/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:46 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/28 10:39:49 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "signal_tp.h"

// reset handlers and change signal for parent process

bool	handle_signal_in_heredoc(char *filename, int here_doc_fd)
{
	bool	return_value;

	reset_sig_handler_to_parent();
	return_value = execute_here_doc(filename, here_doc_fd);
	reset_sig_handler_to_child();
	return (return_value);
}

bool	execute_here_doc(char *filename, int here_doc_fd)
{
	char	*line;
	char	*new_line;

	new_line = NULL;
	while (1)
	{
		if (check_for_interactive_shell () == true)
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		new_line = extend_line(&line);
		if (ft_strcmp(new_line, filename) == true)
			break ;
		ft_putstr_fd(new_line, here_doc_fd);
		if (check_for_interactive_shell() == true)
			ft_putstr_fd("\n", here_doc_fd);
		free(new_line);
		new_line = NULL;
	}
	if (new_line && (*new_line))
		free(new_line);
	close(here_doc_fd);
	return (true);
}

void	change_filename(char *new_tmp_file_name)
{
	int	i;

	i = 0;
	while (new_tmp_file_name[i])
	{
		if (ft_strchr("!?-@#$^&*(){} ", new_tmp_file_name[i]) != NULL)
		{
			new_tmp_file_name[i] = '_';
		}
		i++;
	}
}
