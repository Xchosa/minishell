/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:54:10 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/01 13:56:18 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"
#include <termios.h>


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
		get_exit_codes()->last_exit_code = ec_sucess;
		// ft_putstr_fd("EXIT: 3\n", STDOUT_FILENO);
	}
	else if (sig == SIGTSTP)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
	}
}

void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 130; // sleep and then ctrl + C
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		// ft_putstr_fd("EXIT: 3\n", STDOUT_FILENO);
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		get_exit_codes()->last_exit_code = 131; // sleep and then ctrl + D
	}
	return ;
}

void	init_signal(int is_child)
{
	struct sigaction	sa;

	// sa.sa_flags = SA_RESTART;
	reset_terminal_state();
	sigemptyset(&sa.sa_mask);// clear blocked signals
	//changes signal action (replaces signal() for better control
	if (is_child == 1)
		sa.sa_handler = child_handler;
	else
		sa.sa_handler = parent_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);// ctrl D 
	sigaction(SIGTERM, &sa, NULL);
/// put only in if done 
	// sigaction(SIGTSTP, &sa, NULL); // ignore ctrl + Z
	rl_catch_signals = 0;
}



