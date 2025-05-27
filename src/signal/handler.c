
#include "signal.h"

// allowed functions
// signal,
// sigaction, sigemptyset, sigaddset, 
// getcwd, chdir, stat, lstat, fstat,


// Key	    Signal/Effect	    Default Behavior	    How to Handle in C
// Ctrl+C	SIGINT	            Interrupt/Terminate	    Use signal(SIGINT, handler)
// Ctrl+\	SIGQUIT	            Quit/Core Dump	        Use signal(SIGQUIT, handler)
// Ctrl+D	EOF(not a signal)	End of input (stdin)	Check for EOF in input functions
// EOF	    Value	             End file/stream	     Check for EOF in input functions



// Ctrl + C
// closes the STDIN Pipe ->flushes the current input 
// 2nd time program uses this garabe input
// static void handle_sigint(int sig) 
// {
//     printf("Caught SIGINT (Ctrl+C). Cleaning up...\n");
//     // free(line);
//     // free(token_lst);
//     exit(0);
// }

// Ctrl + 
// Meaning: Sends the SIGQUIT signal to the process.
// pressing Ctrl+\ will invoke your handler 
// instead of terminating the program
// static void handle_sigquit(int sig)
// {
//     printf("Caught SIGQUIT (Ctrl+\\).\n");
// }


// Ctrl+D signals the end-of-file (EOF) condition on the 
// terminal when input is being read in canonical mode.

// fgets()
// scanf()
// returns EOF -> -1 
//How to handle: Check the return value of 
// input functions for EOF.

/*
Fields within termios:
c_iflag: Input flags, controlling how input data is processed. 
c_oflag: Output flags, controlling how output data is sent. 
c_cflag: Control flags, configuring the terminal hardware. 
c_lflag: Local flags, affecting local terminal operations. 
c_cc: An array of special control characters (e.g., INTR, QUIT, ERASE). 

Functions for Terminal Control:
tcgetattr(fd, termios_p): Retrieves the current terminal attributes for a file descriptor 
fd and stores them in the termios structure pointed to by termios_p. 

tcsetattr(fd, optional_actions, termios_p): Sets the terminal attributes for a file descriptor
 fd based on the termios structure pointed to by termios_p. The optional_actions parameter
  specifies how the changes are applied (e.g., immediately, after output drains). 
  
tcdrain(fd): Waits for all output to be transmitted to the terminal. 
tcflush(fd, queue_selector): Flushes input or output data from the terminal queue. 
tcflow(fd, action): Controls flow control (e.g., suspending or restarting output). 
tcsendbreak(fd, duration): Sends a break signal to the terminal. 

*/