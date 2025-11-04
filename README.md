# Lab 10 - Signals
**Course:** CPE 2600 111
**Author:** Ashlyn Dedert
**Date:** 11/4/2025

---

## Overview

These programs explore the use of signals as an inter-processing communication technique, and demonstrates how to register a signal handler and send, suspend, and view pending signals.

### Programs
//TODO update descriptions

# Demonstrations

- **recv_signal.c** - Uses sigaction with SA_SIGINFO to handle SIGUSR1 signals to print a integer (sival_int) sent with sigqueue from another process.
- **send_signal.c** - Sends a SIGUSR1 signal with a random integer to another process using sigqueue. The PID of the receiving process is provided as a command line argument.
- **signal_handler.c** - Sets a signal handler for SIGINT, the handler prints a message and then quits.
- **signal_alarm.c** - sets an alarm for 5 seconds using alarm(), then exits when the signal is received.
- **signal_segfault.c** - Repeatedly catches the dereference of a a segmentation fault.
- **signal_sigaction.c** - demonstrates the use of sigaction with SA_SIGINFO to catch SIGUSR1 and print the sender's PID using siginfo_t.

# Tennis

- **serve_tennis.c** - Sends a signal to the recieving program and passes back and forth, randomly succeeding or failing. Keeps track of score and exits cleanly when a player loses
- **recv_tennis.c** - Recieves a signal from the server and passes back and forth, randomly succeeding or failing. Keeps track of score and exits cleanly when a player loses

## Compilation

 Use the Makfile

 ```make all    # Build all programs```
 
 ```make clean'  # Remove executables and object files```

## Usage
# Demonstrations
 ```./recv_signal```

 ```./send_signal <PID>     # sending```

  ```./signal_handler       # receiving```

 ```./signal_alarm```

 ```./signal_segfault```

  ```./signal_sigaction```

# Tennis

 ```./recv_tennis          # Start in one terminal, prints PID upon start```

 ```./recv_tennis <PID>    # Start in a second terminal to lauch the game```
