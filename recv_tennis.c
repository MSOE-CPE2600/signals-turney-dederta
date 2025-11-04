/**
 * File: recv_tennis.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Waits to receive a SIGUSR1 signal from the serving program
 * Randomly succeeds or fails
 * Keeps track of score and exits cleanly when a player loses
 * 
 * Compile: gcc -o recv_tennis recv_tennis.c OR make
 * Run: ./recv_tennis, then run send_tennis in another terminal
 */

 #define _GNU_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>
 #include <time.h>

 pid_t server_pid = 0;
 int server_score = 0;
 int receiver_score = 0;

 void print_score()
 {
    printf("SCORE - Server: %d | Receiver: %d\n", server_score, receiver_score);
 }


 void handle_ball(int sig, siginfo_t *info, void *context)
 {
    int data = info->si_value.sival_int; // 0 = ball, 1 = server missed
    pid_t server_pid = info->si_pid;

    if (data == 1)
    {
        receiver_score++;
        printf("Server missed! Receiver scores a point\n");
        print_score();
        if (receiver_score >= 4)
        {
            printf("Receiver wins the game!\n");
            exit(0);
        }
        return;
    }

    // receiver tries to return
    sleep(1 + rand() % 2);
    int miss = (rand() % 10 < 2); // 20% miss chance

    if (miss)
    {
        server_score++;
        printf("Receiver: Missed return. Server scores a point\n");
        print_score();
        if (server_score >= 4)
        {
            printf("Server wins the game!\n");
            union sigval val;
            val.sival_int = 1;
            sigqueue(server_pid, SIGUSR1, val);
            exit(0);
        }

        union sigval val;
        val.sival_int = 1;
        sigqueue(server_pid, SIGUSR1, val);
        return;
    }

    // successful return
    printf("Reciever: Hitting ball back to %d\007\n", server_pid);
    union sigval value;
    value.sival_int = 0;
    sigqueue(server_pid, SIGUSR1, value);
    return;
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