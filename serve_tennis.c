/**
 * File: serve_tennis.c
 * Modified by: Ashlyn Dedert
 * CPE 2600 111
 * Lab 10 - Signals
 * 
 * Brief summary of program:
 * Sends a signal to the recieving program and passes back and forth with it
 * ten times before exiting
 * 
 * Compile: gcc -o recv_tennis recv_tennis.c OR make
 * Run: ./recv_tennis in another terminal, then run ./send_tennis
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>
 #include <time.h>
 
 pid_t opponent_pid;

 void handle_ball(int sig, siginfo_t *info, void *context)
 {
    int count = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid;

    printf("Server: Recieved ball from %d, count %d\n", sender_pid, count);
    
    if (count >= 10)
    {
        printf("Server: Game over, final count = %d\n", count);
        exit(0);
    }

    sleep(1 + rand() % 2);

    union sigval value;
    value.sival_int = count + 1;

    printf("Server: Hitting ball back to %d, count %d\007\n", opponent_pid, value.sival_int);
    sigqueue(opponent_pid, SIGUSR1, value);
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
    value.sival_int = 1;
    printf("Server: Serving ball to %d, count %d\a\n", opponent_pid, value.sival_int);
    sigqueue(opponent_pid, SIGUSR1, value);

    while (1)
    {
        pause();
    }
}
