
#include "minishell.h"
#include "parser.h"

// allowed functions
// signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat,


// Key	    Signal/Effect	    Default Behavior	    How to Handle in C
// Ctrl+C	SIGINT	            Interrupt/Terminate	    Use signal(SIGINT, handler)
// Ctrl+\	SIGQUIT	            Quit/Core Dump	        Use signal(SIGQUIT, handler)
// Ctrl+D	EOF(not a signal)	End of input (stdin)	Check for EOF in input functions
// EOF	    Value	             End file/stream	     Check for EOF in input functions

// Ctrl + C
// closes the STDIN Pipe ->flushes the current input 
// 2nd time program uses this garabe input
static void handle_sigint(int sig) 
{
    printf("Caught SIGINT (Ctrl+C). Cleaning up...\n");
    // free(line);
    // free(token_lst);
    exit(0);
}

// Ctrl + \
// Meaning: Sends the SIGQUIT signal to the process.
// pressing Ctrl+\ will invoke your handler 
// instead of terminating the program
static void handle_sigquit(int sig)
{
    printf("Caught SIGQUIT (Ctrl+\\).\n");
}


// Ctrl+D signals the end-of-file (EOF) condition on the 
// terminal when input is being read in canonical mode.

// fgets()
// scanf()
// returns EOF -> -1 
//How to handle: Check the return value of 
// input functions for EOF.





void init_signal(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);

}