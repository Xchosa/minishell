/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:46 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/07 13:16:23 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "signal_tp.h"

// reset handlers and change signal for parent process
bool	execute_here_doc(char *filename, int here_doc_fd)
{
	char	*line;

	reset_sig_handler_to_parent();
	while (1)
	{
		if (check_for_interactive_shell () == true)
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strcmp(line, filename) == true) 
			break ;
		ft_putstr_fd(line, here_doc_fd);
		if (check_for_interactive_shell() == true)
			ft_putstr_fd("\n", here_doc_fd);
	}
	if (line)
		free(line);
	close(here_doc_fd);
	reset_sig_handler_to_child();
	return (true);
}