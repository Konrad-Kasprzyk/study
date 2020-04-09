#include "csapp.h"
#include "signal.h"

volatile int check = 0;

// z SIGUSR1 nic nie robi, ale też go obsługuje
static void signal_handler(int signum, siginfo_t *info, void *data) 
{
    if (signum == SIGINT) 
    {
        safe_printf("(%d) Screw you guys... I'm going home!\n", getpid());
        _exit(0);
    }
}


static void play(pid_t next, const sigset_t *set) 
{
    check = 1;
    Kill(getppid(), SIGCONT);
    for (;;)
    {
        printf("(%d) Waiting for a ball!\n", getpid());
        
        Sigsuspend(set);

        usleep(500 * 1000);
        Kill(next, SIGUSR1);
        printf("(%d) Passing ball to (%d)!\n", getpid(), next);
    }
}


int main(int argc, char *argv[]) 
{
    if (argc != 2)
        app_error("Usage: %s [CHILDREN]", argv[0]);

    int children = atoi(argv[1]);

    if (children < 4 || children > 20)
        app_error("Give number of children in range from 4 to 20!");

    /* Register signal handler for SIGUSR1 */
    // struktura, ktora mowi co robic z sygnalami
    struct sigaction action = { .sa_sigaction = signal_handler };
    // na te sygnaly ustawiamy handler
    Sigaction(SIGUSR1, &action, NULL);
    Sigaction(SIGINT, &action, NULL);

    // dajemy maske tych sygnalow, ale wewnatrz struct
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGUSR1);
    sigaddset(&action.sa_mask, SIGUSR1);
    // blokujemy dla tego sygnalu SIGUSR1 i dajemy do tej samej zmiennej altualną maskę
    Sigprocmask(SIG_BLOCK, &action.sa_mask, &action.sa_mask);

    pid_t next_pid = getpid();

    for (int i = 0; i < children; i++)
    {
        pid_t pid = Fork();

        if (!pid)
            play(next_pid, &action.sa_mask);
        else{
            // by nie nadpisac next_pid zanim dziecko sie wykona
            while(pid == 0)
                Sigsuspend(&action.sa_mask);
        
            next_pid = pid;
            pid = 0;
        }
    }

    Kill(next_pid, SIGUSR1);
    play(next_pid, &action.sa_mask);

    return EXIT_SUCCESS;
}
