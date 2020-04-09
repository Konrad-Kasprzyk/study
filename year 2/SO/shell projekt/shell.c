#include <readline/readline.h>
#include <readline/history.h>

#define DEBUG 0
#include "shell.h"

sigset_t sigchld_mask;

static sigjmp_buf loop_env;

static void sigint_handler(int sig) {
  siglongjmp(loop_env, sig);
}

/* Rewrite closed file descriptors to -1,
 * to make sure we don't attempt do close them twice. */
static void MaybeClose(int *fdp) {
  if (*fdp < 0)
    return;
  Close(*fdp);
  *fdp = -1;
}

/* Consume all tokens related to redirection operators.
 * Put opened file descriptors into inputp & output respectively. */
static int do_redir(token_t *token, int ntokens, int *inputp, int *outputp) {
  token_t mode = NULL; /* T_INPUT, T_OUTPUT or NULL */
  int n = 0;           /* number of tokens after redirections are removed */

  for (int i = 0; i < ntokens; i++) {
    /* TODO: Handle tokens and open files as requested. */

     mode = token[i];
      if(mode == T_INPUT){
        *inputp = open(token[i+1], O_RDONLY | O_CREAT, S_IRWXU);
        token[i] = T_NULL;
        token[i+1] = T_NULL;
        for( int j = i+2; j < ntokens; j++){
          if(token[j] != T_NULL){
            token[i] = token[j];
            token[j] = T_NULL;
            n++;
            break;
          }
        }
      } else if (mode == T_OUTPUT){
        *outputp = open(token[i+1], O_WRONLY | O_CREAT, S_IRWXU);
        token[i] = T_NULL;
        token[i+1] = T_NULL;
        for( int j = i+2; j < ntokens; j++){
          if(token[j] != T_NULL){
            token[i] = token[j];
            token[j] = T_NULL;
            n++;
            break;
          }
        }
      } else if(mode == T_NULL){
        for( int j = i+1; j < ntokens; j++){
          if(token[j] != T_NULL){
            token[i] = token[j];
            token[j] = T_NULL;
            n++;
            break;
          }
        }
      } else {
        n++;
      }
  }

  token[n] = NULL;
  return n;
}

/* Execute internal command within shell's process or execute external command
 * in a subprocess. External command can be run in the background. */
static int do_job(token_t *token, int ntokens, bool bg) {
  int input = -1, output = -1;
  int exitcode = 0;

  ntokens = do_redir(token, ntokens, &input, &output);

  if (!bg) {
    if ((exitcode = builtin_command(token)) >= 0)
      return exitcode;
  }

  sigset_t mask;
  Sigprocmask(SIG_BLOCK, &sigchld_mask, &mask);

  /* TODO: Start a subprocess, create a job and monitor it. */

   pid_t pid = fork();

  if(pid<0){
    Sigprocmask(SIG_SETMASK, &mask, NULL);
    return -1;
  }

  if(pid == 0){
    signal(SIGTSTP, SIG_DFL);
    Signal(SIGTTIN, SIG_DFL);
    Signal(SIGTTOU, SIG_DFL);
    setpgid(0,0);

    if (builtin_command(token) >= 0){
      MaybeClose(&input);
      MaybeClose(&output);
      exit(EXIT_SUCCESS);
    }
    
    if(input>-1)
      dup2(input,STDIN_FILENO);
    
    if(output>-1)
      dup2(output,STDOUT_FILENO);

    MaybeClose(&input);
    MaybeClose(&output);
    Sigprocmask(SIG_SETMASK, &mask, NULL);
    external_command(token);
  }else{ 

    MaybeClose(&input);
    MaybeClose(&output);

    if(bg){
      int j = addjob(pid, bg);
      addproc(j, pid, token);
      printf("[%d] running '",j);
      for(int i = 0; i < ntokens -1 ; i++)
        printf("%s ",token[i]);
      printf("%s'\n",token[ntokens-1]);
      watchjobs(FINISHED);
    }else{
      int j = addjob(pid, bg);
      addproc(j, pid, token);
      exitcode = monitorjob(&mask);
    }
  }

  Sigprocmask(SIG_SETMASK, &mask, NULL);
  return exitcode;
}

/* Start internal or external command in a subprocess that belongs to pipeline.
 * All subprocesses in pipeline must belong to the same process group. */
static pid_t do_stage(pid_t pgid, sigset_t *mask, int input, int output,
                      token_t *token, int ntokens) {
  ntokens = do_redir(token, ntokens, &input, &output);

  if (ntokens == 0)
    app_error("ERROR: Command line is not well formed!");

  /* TODO: Start a subprocess and make sure it's moved to a process group. */

  pid_t pid = fork();

  if(pid<0){
    Sigprocmask(SIG_SETMASK, mask, NULL);
    return -1;
  }

  if(pid == 0){
    signal(SIGTSTP, SIG_DFL);
    Signal(SIGTTIN, SIG_DFL);
    Signal(SIGTTOU, SIG_DFL);

    if (builtin_command(token) >= 0){
      MaybeClose(&input);
      MaybeClose(&output);
      exit(EXIT_SUCCESS);
    }
      
    if(input>-1)
      dup2(input,STDIN_FILENO);
    
    if(output>-1)
      dup2(output,STDOUT_FILENO);
    
    MaybeClose(&input);
    MaybeClose(&output);   
    Sigprocmask(SIG_SETMASK, mask, NULL);
    external_command(token);  
  }
  setpgid(pid, pgid);

  return pid;
}

static void mkpipe(int *readp, int *writep) {
  int fds[2];
  Pipe(fds);
  fcntl(fds[0], F_SETFD, FD_CLOEXEC);
  fcntl(fds[1], F_SETFD, FD_CLOEXEC);
  *readp = fds[0];
  *writep = fds[1];
}

static bool is_pipeline(token_t *token, int ntokens) {
  for (int i = 0; i < ntokens; i++)
    if (token[i] == T_PIPE)
      return true;
  return false;
}

/* Pipeline execution creates a multiprocess job. Both internal and external
 * commands are executed in subprocesses. */
static int do_pipeline(token_t *token, int ntokens, bool bg) {
  pid_t pid, pgid = 0;
  int job = -1;
  int exitcode = 0;

  int input = -1, output = -1, next_input = -1;

  mkpipe(&next_input, &output);

  sigset_t mask;
  Sigprocmask(SIG_BLOCK, &sigchld_mask, &mask);

  /* TODO: Start pipeline subprocesses, create a job and monitor it.
   * Remember to close unused pipe ends! */

  // pozycja gdzie jest T_PIPE w tablicy token
  int n=0;
  for(int i=0; token[i]!=T_PIPE; i++){
    n++;
  }

  // zawiera wybrane tokeny do procesu w do_stage, gdzie miejsce T_PIPE zastąpiono T_NULL (na końcu token2)
  token_t *token2 = malloc(sizeof(token_t) * (n + 1));

  for(int i=0; i<n; i++){
    token2[i] = token[i];
  }

  token2[n] = T_NULL;
  fcntl(next_input, F_SETFL, O_CLOEXEC);
  pid = do_stage(getpgrp(), &mask, -1, output, token2, n+1);

  // ustaw grupę procesu zrobionego w do_stage na jego pid
  setpgid(pid, pid);
  pgid = pid;
  job = addjob(pgid,bg);
  addproc(job, pid, token2);
  token[n] = T_NULL;
  free(token2);

  // pozycja gdzie jest następny T_PIPE w tablicy token
  int n2 = n;

  // wewnętrzne procesy potoku
  while(is_pipeline(token, ntokens)){
    for(int i=n; token[i]!=T_PIPE; i++){
      n2++;
    }

    token2 = malloc(sizeof(token_t) * (n2 - n));
    token[n2] = T_NULL;

    for(int i=0; i<n2 - n; i++){
      token2[i] = token[i + n + 1];
    }

    Close(output);
    mkpipe(&input, &output);
    pid = do_stage(pgid, &mask, next_input, output, token2, n2 - n);
    Close(next_input);
    next_input = input;
    n = n2;
    addproc(job, pid, token2);
    free(token2);
  }
  
  // proces po ostatnim T_PIPE
  token2 = malloc(sizeof(token_t) * (ntokens - n));

  for(int i=0; i<ntokens - n - 1; i++){
    token2[i] = token[i + n + 1];
  }

  token2[ntokens - n - 1] = T_NULL;
  Close(output);
  pid = do_stage(pgid, &mask, next_input, -1, token2, ntokens - n - 1);
  Close(next_input);
  addproc(job, pid, token2);
    
  if(!bg)
    exitcode = monitorjob(&mask);
  else{
    int i;
    bool spacja = false;
    printf("[%d] running '",job);
    for(i = 0; i<ntokens -1; i++){
      if(token[i] == T_INPUT || token[i] == T_OUTPUT){
        i+=2;
        continue;
      }
      if(spacja){
        printf(" ");
        spacja = false;
      }
      if(token[i] == T_NULL){
        printf("|");
        spacja = true;
      } 
      else{
        printf("%s",token[i]);
        spacja = true;
      }
    }
    if(i==ntokens-1)
      printf("%s'\n",token[ntokens-1]);
    else
      printf("'\n");
    
    watchjobs(FINISHED);
  }
  free(token2);

  Sigprocmask(SIG_SETMASK, &mask, NULL);
  return exitcode;
}

static void eval(char *cmdline) {
  bool bg = false;
  int ntokens;
  token_t *token = tokenize(cmdline, &ntokens);

  if (ntokens > 0 && token[ntokens - 1] == T_BGJOB) {
    token[--ntokens] = NULL;
    bg = true;
  }

  if (ntokens > 0) {
    if (is_pipeline(token, ntokens)) {
      do_pipeline(token, ntokens, bg);
    } else {
      do_job(token, ntokens, bg);
    }
  }

  free(token);
}

int main(int argc, char *argv[]) {
  rl_initialize();

  sigemptyset(&sigchld_mask);
  sigaddset(&sigchld_mask, SIGCHLD);

  Setpgid(0, 0);

  initjobs();

  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, SIG_IGN);
  Signal(SIGTTIN, SIG_IGN);
  Signal(SIGTTOU, SIG_IGN);

  char *line;
  while (true) {
    if (!sigsetjmp(loop_env, 1)) {
      line = readline("# ");
    } else {
      msg("\n");
      continue;
    }

    if (line == NULL)
      break;

    if (strlen(line)) {
      add_history(line);
      eval(line);
    }
    free(line);
    watchjobs(FINISHED);
  }

  msg("\n");
  shutdownjobs();

  return 0;
}
