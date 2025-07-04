/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:02 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/04 17:40:02 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

bool	ft_first_node(int fd[][2])
{
	close(fd[0][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		return (false);
	close (fd[0][1]);
	return (true);
}

bool	ft_middle_node(int fd[][2], t_cmd_list *cmd_list, t_cmd_node *cmd_node)
{
	int			i;
	t_cmd_node	*current;

	current = cmd_list->head;
	i = 0;
	while (current != cmd_node)
	{
		i++;
		current = current->next;
	}
	close(fd[i][0]);
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0 || dup2(fd[i][1],
			STDOUT_FILENO) < 0)
		return (false);
	close(fd[i - 1][0]);
	close(fd[i][1]);
	return (true);
}

bool	ft_last_node(int fd [][2], t_cmd_list *cmd_list)
{
	int	i;

	i = cmd_list->size - 2;
	if (dup2(fd[i][0], STDIN_FILENO) < 0)
		return (false);
	close (fd[i][0]);
	return (true);
}

void	ft_close_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2])
{
	int			i;
	t_cmd_node	*current;

	current = cmd_list->head;
	i = 0;
	while (current != cmd_node)
	{
		i++;
		current = current->next;
	}
	while (i < cmd_list->size - 2)
	{
		close(fd[i + 1][0]);
		close(fd[i + 1][1]);
		i++;
	}
}

bool	ft_manage_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2])
{
	bool	check;

	check = true;
	ft_close_pipes(cmd_list, cmd_node, fd);
	if (cmd_node == cmd_list->head)
		check = ft_first_node(fd);
	else if (cmd_node == cmd_list->tail)
		check = ft_last_node(fd, cmd_list);
	else
		check = ft_middle_node(fd, cmd_list, cmd_node);
	return (check);
}
