
#include "signal_tp.h"
#include <termios.h>


void	heredoc_signal(int is_child)
{
	struct sigaction sa;

	// sa.sa_flags = SA_RESTART;
	reset_terminal_state();
	sigemptyset(&sa.sa_mask);
	// clear blocked signals
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

void	heredoc_handler(int sig)
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