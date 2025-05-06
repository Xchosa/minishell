/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:52 by tschulle          #+#    #+#             */
/*   Updated: 2025/05/06 17:49:06 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	ft_manage_redirections(t_cmd_node *cmd_node, int fd[][2])
{
	t_file_node	*current;

	current = cmd_node->file_list->head;
	while (current != NULL)
	{
		if (current->redir_type == 1)
			ft_manage_infile(current->filename, fd);
		else if (current->redir_type == 2)
			ft_manage_outfile(current->filename, fd);
		else if (current->redir_type == 3)
			ft_manage_append(current->filename, fd);
		current = current->next;
	}
}
