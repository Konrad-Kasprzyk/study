#include "shell.h"

typedef struct {
  pid_t pid;           /* 0 if slot is free */
  sig_atomic_t status; /* -1 if exit status not yet received */
} job_t;

static job_t *jobs = NULL;
static int njobmax = 1;

// ustawia exitstatus w tablicy jobs każdemu procesowi, który się zakończył. Nie zmienia pid na 0, przez co jest to nadal zajęte zadanie.
// Dopiero jobdone to zmieni na wolne zadanie zmieniając pid na 0 i exitstatus na -1, gdy wyjdziemy z handlera
static void sigchld_handler(int sig) {
  int old_errno = errno;
  pid_t pid;
  int status;
  /* TODO: Bury all children that finished saving their status in jobs. */
  for (int job = 0; job < njobmax; job++) {
    pid = jobs[job].pid;
    // gdy proces nie zmienił statusu, to waitpid zwróci 0 dzięki WNOHANG. Waitpid pochowa dziecko
    if (pid && waitpid(pid, &status, WNOHANG)) {
      // zapisz exit status. Funkcja jobdone zmieni pid na zero i wypisze status
      jobs[job].status = status;
    }
  }

  errno = old_errno;
}

jobid_t addjob(pid_t pid, bool bg) {
  int jobidx = -1;

  if (bg) {
    /* Find empty slot for background job. */
    for (int i = JOBID_BG; i < njobmax; i++) {
      if (jobs[i].pid == 0) {
        jobidx = i;
        break;
      }
    }

    /* If none found, allocate new one. */
    if (jobidx < 0) {
      jobidx = njobmax++;
      jobs = realloc(jobs, sizeof(job_t) * njobmax);
    }
  } else {
    jobidx = JOBID_FG;
  }

  jobs[jobidx] = (job_t){.pid = pid, .status = -1};

  if (jobidx)
    msg("[%d] %d\n", jobidx, pid);

  return jobidx;
}

// ustawia zakończone zadania na dostępne i wypisuje ich exit status
void watchjobs(void) {
  for (int i = JOBID_BG; i < njobmax; i++) {
    int wstatus = jobs[i].status;

    if (wstatus >= 0) {
      msg("[%d] ", i);
      if (WIFEXITED(wstatus)) {
        msg("exited, status=%d\n", WEXITSTATUS(wstatus));
      } else if (WIFSIGNALED(wstatus)) {
        msg("killed by signal %d\n", WTERMSIG(wstatus));
      } else if (WIFSTOPPED(wstatus)) {
        msg("stopped by signal %d\n", WSTOPSIG(wstatus));
      } else if (WIFCONTINUED(wstatus)) {
        msg("continued\n");
      }
      jobs[i] = (job_t){.pid = 0, .status = -1};
    }
  }
}

// jeśli zadanie się zakończyło to ustawia je w tablicy jobs na dostępne i wypisuje exit status
int jobdone(jobid_t jobidx) {
  assert(jobidx < njobmax);
  job_t *job = &jobs[jobidx];
  assert(job->pid);
  int status = job->status;
  if (status >= 0)
    *job = (job_t){.pid = 0, .status = -1};
  return status;
}

void initjobs(void) {
  Signal(SIGCHLD, sigchld_handler);
  jobs = calloc(sizeof(job_t), 1);
}

void killjob(jobid_t jobidx, int sig) {
  if (jobidx == JOBID_EVERY) {
    for (int i = 0; i < njobmax; i++)
      if (jobs[i].pid) {
        msg("[%d] Killing %d\n", i, jobs[i].pid);
        kill(jobs[i].pid, sig);
      }
  } else {
    assert(jobidx < njobmax);
    job_t *job = &jobs[jobidx];
    if (job->pid) {
      if (jobidx != JOBID_FG)
        msg("[%d] Killing %d\n", jobidx, job->pid);
      kill(job->pid, sig);
    }
  }
}
