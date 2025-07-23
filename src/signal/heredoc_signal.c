
#include "signal_tp.h"


void	heredoc_signal(int is_child)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	reset_terminal_state();
	sigemptyset(&sa.sa_mask);
	if (is_child == 1)
		sa.sa_handler = child_handler;
	else
		sa.sa_handler = heredoc_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 130;
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
		exit(1);
	}
	else if (sig == SIGTSTP)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
	}
}
