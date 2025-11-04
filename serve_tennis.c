/**
 * File: serve_tennis.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Sends a signal to the recieving program and passes back and forth
 * Randomly succeeds or fails
 * Keeps track of score and exits cleanly when a player loses
 * 
 * Compile: gcc -o recv_tennis recv_tennis.c OR make
 * Run: ./recv_tennis in another terminal, then run ./send_tennis
 */

 #define _GNU_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>
 #include <time.h>
 
 pid_t opponent_pid;
 int server_score = 0;
 int receiver_score = 0;

 void print_score()
 {
    printf("SCORE - Server: %d | Receiver: %d\n", server_score, receiver_score);
 }

 void serve_ball()
 {
    sleep(1);
    union sigval val;
    val.sival_int = 0;
    printf("Server: Serving the ball\007\n");
    sigqueue(opponent_pid, SIGUSR1, val);
 }

 void handle_ball(int sig, siginfo_t *info, void *context)
 {
    int data = info->si_value.sival_int; // 0 = ball, 1 = server missed
    pid_t opponent_pid = info->si_pid;

    if (data == 1)
    {
        server_score++;
        printf("Receiver missed! Server scores a point\n");
        print_score();

        if (server_score >= 4)
        {
            printf("Server wins the game!\n");
            exit(0);
        }

        // Serve again after scoring
        serve_ball();
        return;
    }

    // Server tries to return
    sleep(1 + rand() % 2);
    int miss = (rand() % 10 < 2); // 20% miss chance

    if (miss)
    {
        receiver_score++;
        printf("Server: Missed return. Receiver scores a point\n");
        print_score();
        if (receiver_score >= 4)
        {
            printf("Receiver wins the game!\n");
            union sigval val;
            val.sival_int = 1;
            sigqueue(opponent_pid, SIGUSR1, val);
            exit(0);
        }

        // tell receiver they scored
        union sigval val;
        val.sival_int = 1;
        sigqueue(opponent_pid, SIGUSR1, val);

        serve_ball();
        return;
    }

    // successful return
    printf("Server: Hitting ball back to %d\007\n", opponent_pid);
    union sigval value;
    value.sival_int = 0;
    sigqueue(opponent_pid, SIGUSR1, value);
    return;
 }

 int main(int argc, char *argv[])
 {
    if (argc != 2)
    {
        fprintf(stderr, "Useage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    opponent_pid = atoi(argv[1]);

    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    printf("Server PID: %d, Opponent PID: %d\n", getpid(), opponent_pid);

    // Serve first ball
    union sigval value;
    value.sival_int = 0;
    printf("Server: Serving ball to %d, count %d\a\n", opponent_pid, value.sival_int);
    sigqueue(opponent_pid, SIGUSR1, value);

    while (1)
    {
        pause();
    }
}
