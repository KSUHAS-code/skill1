#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int sig)
{
    if (sig == SIGUSR1)
        printf("\nReceived SIGUSR1\n");

    else if (sig == SIGINT) {
        printf("\nReceived SIGINT. Exiting...\n");
        exit(0);
    }

    else if (sig == SIGTERM) {
        printf("\nReceived SIGTERM. Exiting gracefully...\n");
        exit(0);
    }
}

int main()
{
    signal(SIGUSR1, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("Signal handler started.\n");
    printf("PID = %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1)
        pause();

    return 0;
}
