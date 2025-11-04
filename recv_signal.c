/**
 * File: recv_signal.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Uses sigaction with SA_SIGINFO to handle SIGUSR1 signals to print a integer
 * (sival_int) sent with sigqueue from another process.
 * 
 * Usage:
 * 1. Run this program ./recv_signal
 * 2. Note the printed PID and run send_signal in another terminal.
 */

#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signal, siginfo_t *info, void *context)
{
    if (signal == SIGUSR1)
    {
        printf("Received SIGUSR1 with value: %d\n", info->si_value.sival_int);
        exit(0);
    }
}

int main()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for SIGUSR1 with data...\n");

    while (1)
    {
        pause(); // wait for signals
    }

    return 0;
}