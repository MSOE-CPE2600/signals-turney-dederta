/**
 * File: recv_tennis.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Waits to receive a SIGUSR1 signal from the serving program, then passes it back
 * and forth ten more times before exiting
 * 
 * Compile: gcc -o recv_tennis recv_tennis.c OR make
 * Run: ./recv_tennis, then run send_tennis in another terminal
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>
 #include <time.h>

 void handle_ball(int sig, siginfo_t *info, void *context)
 {
    int count = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid;

    printf("Reciever: Got ball from %d with count %d\n", sender_pid, count);

    // wait random 1-2 seconsds
    sleep(1 + rand() % 2);

    union sigval value;
    value.sival_int = count + 1;

    printf("Reciever: Hitting ball back to %d with count %d\007\n", sender_pid, value.sival_int);
    sigqueue(sender_pid, SIGUSR1, value);

    if (count >= 9)
    {
        printf("Reciever: Game over, exiting..\n");
        exit(0);
    }
 }

 int main()
 {
    srand(time(NULL));
    printf("Reciever: PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        pause(); // wait forever
    }
 }