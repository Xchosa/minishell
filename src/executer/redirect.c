/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:52 by tschulle          #+#    #+#             */
/*   Updated: 2025/06/23 13:35:34 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executer.h"

void	ft_manage_infile(char *infile, int fd[][2])
{
	int	in_fd;

	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
		return ;
	if (dup2(in_fd, STDIN_FILENO) < 0)
		return ;
	close (in_fd);
	return ;
}

void	ft_manage_outfile(char *outfile, int fd[][2])
{
	int	out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd < 0)
		return ;
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		return ;
	close (out_fd);
	return ;
}

void	ft_manage_append(char *appendfile, int fd[][2])
{
	int	ap_fd;

	ap_fd = open(appendfile, O_WRONLY | O_APPEND | O_CREAT);
	if (ap_fd < 0)
		return ;
	if (dup2(ap_fd, STDOUT_FILENO) < 0)
		return ;
	close(ap_fd);
	return ;
}

void	ft_manage_heredoc(char *delimiter, int fd[][2])
{
	char	*next;

	next = get_next_line(0);
	while (next != NULL)
	{
		if (ft_strncmp(next, delimiter, ft_strlen(delimiter)) == 0)
			break;
		write(1, next, ft_strlen(next));
		free(next);
		next = get_next_line(0);
		//ft_printf("%dn", ft_strncmp(next, delimiter, ft_strlen(delimiter)));
	}
	free(next);
	return ;
}


void	ft_manage_redirections(t_cmd_node *cmd_node, int fd[][2])
{
	t_file_node	*current;

	current = cmd_node->file_list->head;
	while (current != NULL)
	{
		if (current->redir_type == REDIRECT_INPUT)
			ft_manage_infile(current->filename, fd);
		else if (current->redir_type == REDIRECT_OUTPUT)
			ft_manage_outfile(current->filename, fd);
		else if (current->redir_type == HERE_DOC)
			ft_manage_heredoc(current->filename, fd);
		else if (current->redir_type == APPEND)
			ft_manage_append(current->filename, fd);
		current = current->next;
	}
}
