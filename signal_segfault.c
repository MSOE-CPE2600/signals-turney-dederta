/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Ashlyn Dedert
 * 
 * Brief summary of modifications:
 * - added a signal handler for SIGSEGV that prints a message when a segmentation fault occurs
 * - demonstrates what happens when you don't exit after catching.
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void segfault_handler(int signal)
{
    if (signal == SIGSEGV)
    {
        printf("SIGSEGV caught: null pointer dereference\n");
    }
}

int main (int argc, char* argv[]) {
    // Register signal handler
    signal(SIGSEGV, segfault_handler);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}