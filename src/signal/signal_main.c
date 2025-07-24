/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:54:10 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/24 10:00:23 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"

void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = EC_SUCESS;
	}
	else if (sig == SIGTSTP)
	{
		get_exit_codes()->last_exit_code = EC_SUCESS;
	}
}

void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		get_exit_codes()->last_exit_code = 131;
	}
	return ;
}

void	init_signal(int is_child)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	reset_terminal_state();
	sigemptyset(&sa.sa_mask);
	if (is_child == 1)
		sa.sa_handler = child_handler;
	else if (is_child == 0)
		sa.sa_handler = parent_handler;
	else if (is_child == 2)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		return ;
	}
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	rl_catch_signals = 0;
}
