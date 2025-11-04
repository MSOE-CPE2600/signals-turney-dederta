/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Ashlyn Dedert
 * 
 * Brief summary of modifications:
 *  - removed the exit() call from the signal handler.
 *  - added a global flag so main can exit gracefully after receiving SIGINT
 *  - added PID printout for testing with the kill command.
 * 
 * Compile: gcc -o signal_handler signal_handler.c
 * Run: ./signal_handler
 * Interupt with CTRL-C or kill <PID> from another terminal
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

volatile sig_atomic_t signal_received = 0;

/**
 * @brief Signal handler for SIGINT - prints a message and sets a flag
 */
void handle_signal(int signal) {
    printf("\nReceived SIGINT, signal number: %d\n", signal);
    signal_received = 1; // mark SIGINT as received
}

int main() {

    printf("PID %d\n", getpid());
    printf("Waiting for SIGINT (Press Ctrl+C)...\n");

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
        if (signal_received) {
            printf("Exiting gracefully after receiving SIGINT.\n");
            break; // exit the loop and terminate the program
        }
    }

    return 0;
}