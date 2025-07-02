
#include "signal_tp.h"
#include <termios.h>



// Key	    Signal/Effect	    Default Behavior	    How to Handle in C
// Ctrl+C	SIGINT	            Interrupt/Terminate	    Use signal(SIGINT, handler)
// Ctrl+\	SIGQUIT	            Quit/Core Dump	        Use signal(SIGQUIT, handler)
// Ctrl+D	EOF(not a signal)	End of input (stdin)	Check for EOF in input functions
// Ctrl+Z   SIGTSTP	            Stop (suspend) process	Use signal(SIGTSTP, handler) or ignore with SIG_IGN                   
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

void reset_sig_handler_to_parent(void)
{
	signal(SIGINT,SIG_DFL); // reset
	heredoc_signal(0);
}
void reset_sig_handler_to_child(void)
{
	signal(SIGINT,SIG_DFL); // reset
	init_signal(1);
}

void hide_ctrl_in_terminal(void)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}
void reset_terminal_state(void)
{
	struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

    tcflush(STDIN_FILENO, TCIFLUSH);
	// fflush(stdout);
}

// for heredoc // implementier heredoc funtionen und danach reset handler
//reset handlers and change signal for parent process
// bei ctrl D soll process beendien -> nur heredoc beenden rest soll weiter gehen  -> korrekt



// cat <<1<<1<<1
// bei ctrl c soll aus allen heredocs raus
// ctrol D nur aus eins - funktioniert 
void heredoc_signal(int is_child)
{
	struct sigaction sa;

	// sa.sa_flags = SA_RESTART;
	reset_terminal_state();
	sigemptyset(&sa.sa_mask);// clear blocked signals
	//changes signal action (replaces signal() for better control
	if(is_child == 1)
		sa.sa_handler = child_handler;
	else
		sa.sa_handler = heredoc_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);// ctrl D 
	sigaction(SIGTERM, &sa, NULL);
}

void heredoc_handler(int sig)
{
    if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 130;
	// in readline mode then only print new line
		write(STDOUT_FILENO, "\n", 1);
		exit(130); // sig int = 2 -> 128 + 2 = 130  // check bash
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
		exit(1);// ft_putstr_fd("EXIT: 3\n", STDOUT_FILENO);
	}
	else if (sig == SIGTSTP)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
	}
}

