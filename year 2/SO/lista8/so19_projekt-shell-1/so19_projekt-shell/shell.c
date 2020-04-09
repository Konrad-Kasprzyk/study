#include <editline/readline.h>

#define DEBUG 0
#include "shell.h"

static int command(char **argv, bool bg) {
  int exitcode = 0;

  if ((exitcode = builtin_command(argv)) >= 0)
    return exitcode;

  sigset_t sigchld_mask, prev_mask;
  /* TODO: Block SIGCHLD temporarily. */
  sigemptyset(&sigchld_mask);
  sigemptyset(&prev_mask);
  sigaddset(&sigchld_mask, SIGCHLD);
  // SIG_BLOCK -> maska blokujących sygnałów jest połączeniem obecnej maski i maski w argumencie, czyli sigchld_mask
  sigprocmask(SIG_BLOCK, &sigchld_mask, &prev_mask);

  pid_t pid = Fork();
  if (pid == 0) {
    // child
    /* TODO: Restore signal mask and put new process into separate group. */
    // SIG_SETMASK -> ustaw maskę blokujących sygnałów jaka jest w argumencie prev_mask
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    // ustawia grupe procesu. setpgid(pid, pgid) jeśli ma pid=0 to bierze obecny proces i jeśli pgid=0 to ustawia grupę tego procesu równą jego pid
    setpgid(0, 0);
    external_command(argv);
  }

  jobid_t jid = addjob(pid, bg);

  if (!bg) {
    while (true) {
      exitcode = jobdone(jid);
      /* TODO: If job is not done then wait for SIGCHLD, otherwise break. */
      // jobdone zwraca status zadania. Gdy jest -1 to znaczy że nie zakończyło się. Gdy jest >=0 to jobdone zmienia te zadanie na dostępne w tablicy jobs
      if (exitcode <= -1) {
        // przywraca maskę z prev_mask. Czeka na obsłużenie sygnału kończącego proces i przywraca obecną maskę
        Sigsuspend(&prev_mask);
      } else
          break;
    }
  }

  /* TODO: Restore signal mask. */
  sigprocmask(SIG_SETMASK, &prev_mask, NULL);

  return exitcode;
}

static int eval(char *cmdline) {
  int argc;
  int exitcode = 0;
  token_t *argv = tokenize(cmdline, &argc);

  if (argc > 0) {
    bool bg = false;

    if (argc > 1 && argv[argc - 1] == T_BGJOB) {
      argv[--argc] = NULL;
      bg = true;
    }

    for (int i = 0; argv[i]; i++) {
      if (string_p(argv[i]))
        debug("argv[%d] = \"%s\"\n", i, argv[i]);
      else
        debug("argv[%d] = %ld\n", i, (long)argv[i]);
    }

    exitcode = command(argv, bg);
  }

  free(argv);

  return exitcode;
}

int main(int argc, char *argv[]) {
  rl_readline_name = "ii-sh";
  rl_catch_signals = 1;
  rl_initialize();

  initjobs();

  char *line;
  while (true) {
    __unused int exitcode = 0;
    line = readline("# ");

    if (line == NULL)
      break;

    add_history(line);
    exitcode = eval(line);
    debug("exitcode = %d\n", WEXITSTATUS(exitcode));
    free(line);
    watchjobs();
  }

  msg("\n");
  killjob(JOBID_EVERY, SIGINT);

  return 0;
}
