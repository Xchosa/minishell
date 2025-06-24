/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:02 by tschulle          #+#    #+#             */
/*   Updated: 2025/06/24 10:49:22 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executer.h"

void	ft_open_pipes(int fd[][2], t_cmd_list *cmd_list)
{
	int	i;

	i = 0;
	while (i < cmd_list->size - 1)
	{
		if (pipe(fd[i]) != 0)
			return ;
		i++;
	}
}

void	ft_open_pipe(int fd[][2], t_cmd_list *cmd_list)
{
	int	i;

	i = 0;
	while (i < cmd_list->size - 1)
	{
		if (pipe(fd[i]) != 0)
			return ;
		i++;
	}
}


//dfdff
// openpipes
// 

void	ft_first_node(int fd[][2])
{
	close(fd[0][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		return ;
	close (fd[0][1]);
}

void	ft_middle_node(int fd[][2], t_cmd_list *cmd_list, t_cmd_node *cmd_node)
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
	//close(fd[i - 1][1]); is schon zu?
	close(fd[i][0]);
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0 || dup2(fd[i][1],
			STDOUT_FILENO) < 0)
		return ;
	close(fd[i - 1][0]);
	close(fd[i][1]);
}

void	ft_last_node(int fd [][2], t_cmd_list *cmd_list)
{
	int	i;

	i = cmd_list->size - 2;
	//close (fd[i][1]);
	if (dup2(fd[i][0], STDIN_FILENO) < 0)
		return ;
	close (fd[i][0]);
}

void	ft_close_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2]) // hier werden die "hohen" pipe fd geschlosssen damit im child nur die offen sind die benoetigt werden
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

void	ft_manage_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2])
{
	ft_close_pipes(cmd_list, cmd_node, fd);
	if (cmd_node == cmd_list->head)
		ft_first_node(fd);
	else if (cmd_node == cmd_list->tail)
		ft_last_node(fd, cmd_list);
	else
		ft_middle_node(fd, cmd_list, cmd_node);
}
