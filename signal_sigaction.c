/**
 * File: signal_sigaction.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * 
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
        printf("Received SIGUSR1 from PID: %d\n", info->si_pid);
    }
}

int main()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // important to get siginfo_t populated
    if (sigaction(SIGUSR1, &sa, NULL) == -1) 
    {
        perror("sigaction");
        return 1;
    }
    printf("Process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1 signal...\n");

    while (1)
    {
        pause(); // wait for signals
    }

    return 0;
}