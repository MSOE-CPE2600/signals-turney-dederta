/**
 * File: signal_alarm.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * This program sets an alarm for 5 seconds using alarm(), 
 * then exits when the signal is received.
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void alarm_handler(int signal)
{
    if (signal == SIGALRM)
    {
        printf("SIGALRM received: alarm fired\n");
        exit(0);
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Setting alarm for 5 seconds...\n");
    alarm(5); // set alarm for 5 seconds

    while (1)
    {
        pause(); // wait for signals
    }

    return 0;
}