/**
 * File: send_signal.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Sends a SIGUSR1 signal with a random integer to another process using sigqueue
 * The PID of the receiving process is provided as a command line argument.
 * 
 * Usage:
 *     ./send_signal <PID>
 */

 #include <signal.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <time.h>

 int main(int argc, char* argv[])
 {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    srand(time(NULL));

    int value = rand() % 100;
    printf("Sending SIGUSR1 with value: %d to PID: %d\n", value, pid);

    union sigval sig_data;
    sig_data.sival_int = value;

    if (sigqueue(pid, SIGUSR1, sig_data) == -1)
    {
        perror("sigqueue");
        return 1;
    }

    printf("Signal sent successfully. \n");
    return 0;
 }