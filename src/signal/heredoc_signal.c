/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:00:40 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/24 15:58:10 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		exit_heredoc_clean();
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = EC_SUCESS;
		exit(1);
	}
	else if (sig == SIGTSTP)
	{
		get_exit_codes()->last_exit_code = EC_SUCESS;
	}
}

void	exit_heredoc_clean(void)
{
	int	exit_code;

	clean_cmd_lst(get_bash()->cmd_garbage);
	exit_code = get_exit_codes()->last_exit_code;
	clean_bash_env();
	clean_exit_codes();
	delete_tmp_files("/tmp");
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exit(exit_code);
}
