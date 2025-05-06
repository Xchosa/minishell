/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:15 by tschulle          #+#    #+#             */
/*   Updated: 2025/05/06 18:05:29 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executer.h"
#include <unistd.h>
#include "pipex.c"
#include "redirect.c"
#include "manage_pipes.c"

void	ft_execute_builtin(t_cmd_node *cmd_node)
{
	(void) cmd_node;
	ft_printf("i am in builtin execution");
}

void	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	path = ft_getpath(cmd_node->cmd[0], envp);
	if (path == NULL)
		return ;//error free exit
	//fprintf(stderr, "%s\n", cmd_node->cmd[0]);
	execve(path, cmd_node->cmd, envp); //errorcheck
}

void	ft_execute_node(
	t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	// ft_printf("%s\n", cmd_node->cmd[0]);
	// ft_printf("%s\n", cmd_node->file_list->head->filename);
	if (cmd_list->size > 1)
		ft_manage_pipes(cmd_list, cmd_node, fd);
	ft_manage_redirections(cmd_node, fd);
	if (cmd_node->cmd_type == 2)
		ft_execute_command(cmd_node, envp);
	else if (cmd_node->cmd_type == 1)
		ft_execute_builtin(cmd_node);
}

void	ft_execute(t_cmd_list *cmd_list, char **envp)
{
	t_cmd_node	*current;
	int			pid;
	int			fd[(int)cmd_list->size][2];
	int			i;

	// if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
	// 	return ; // sonderfall ohne fork; warum?
	i = 0;
	current = cmd_list->head;
	if (cmd_list->size > 1)
		ft_open_pipes(fd, cmd_list);
	while (current != NULL)
	{
		pid = fork();
		if (pid == 0)
			ft_execute_node(cmd_list, current, fd, envp);
		wait(0);
		current = current->next;
		if (i < cmd_list->size - 1)
			close(fd[i][1]);
		if (i > 0 && i < cmd_list->size - 1)
			close(fd[i - 1][0]);
		i++;
	}
	if (cmd_list->size > 1)
		close(fd[i - 1][0]);
}
int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	cmd_list;
	t_cmd_node	cmd_node1;
	t_file_list	file_list1;
	t_file_node file_node1;
	t_file_node file_node2;
	t_file_node	file_node3;

	(void)argc;
	(void)argv;
	cmd_list.head = &cmd_node1;
	cmd_list.tail = NULL;
	cmd_list.size = 1;
	cmd_node1.cmd_type = 2;
	cmd_node1.cmd = ft_split("head -n 5", ' ');
	cmd_node1.file_list = &file_list1;
	cmd_node1.next = NULL;
	file_list1.head = &file_node1;
	file_list1.tail = NULL;
	file_list1.size = 3;
	file_node1.filename = "eingabe";
	file_node1.next = &file_node2;
	file_node1.redir_type = 1;
	file_node2.filename = "ausgabe";
	file_node2.next = &file_node3;
	file_node2.redir_type = 2;
	file_node3.filename = "ausgabe2";
	file_node3.redir_type = 3;
	file_node3.next = NULL;
ft_execute(&cmd_list, envp);
}


//test for priority of pipes vs redirects;
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_node file_node1;
// 	t_file_node file_node2;
// 	t_file_node	file_node3;

// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node2;
// 	cmd_list.size = 2;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 3", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 2;
// 	file_node1.filename = "ausgabe";
// 	file_node1.next = &file_node2;
// 	file_node1.redir_type = 2;
// 	file_node2.filename = "eingabe";
// 	file_node2.next = NULL;
// 	file_node2.redir_type = 1;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("head -n 2", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	file_list2.head = &file_node3;
// 	file_list2.size = 1;
// 	file_list2.tail = NULL;
// 	file_node3.filename = "test";
// 	file_node3.next = NULL;
// 	file_node3.redir_type = 1;
// 	cmd_node2.next = NULL;
// 	ft_execute(&cmd_list, envp);
// }

//test for multiple pipes
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_cmd_node	cmd_node3;
// 	t_cmd_node	cmd_node4;
// 	t_cmd_node	cmd_node5;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_list file_list3;
// 	t_file_list file_list4;
// 	t_file_list	file_list5;
// 	t_file_node file_node1;
// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node5;
// 	cmd_list.size = 5;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 8", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 1;
// 	file_node1.filename = "Eingabe";
// 	file_node1.next = NULL;
// 	file_node1.redir_type = 1;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("head -n 7", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	cmd_node2.next = &cmd_node3;
// 	file_list2.head = NULL; //&file_node5;
// 	file_list2.size = 0;
// 	file_list2.tail = NULL;
// 	cmd_node3.cmd_type = 2;
// 	cmd_node3.cmd = ft_split("tail -n 3", ' ');
// 	cmd_node3.file_list = &file_list3;
// 	cmd_node3.next = &cmd_node4;
// 	file_list3.head = NULL;
// 	file_list3.tail = NULL;
// 	file_list3.size = 0;
// 	cmd_node4.cmd_type = 2;
// 	cmd_node4.cmd = ft_split("head -n 2", ' ');
// 	cmd_node4.next = &cmd_node5;
// 	cmd_node4.file_list = &file_list4;
// 	file_list4.head = NULL;
// 	file_list4.tail = NULL;
// 	file_list4.size = 0;
// 	cmd_node5.cmd_type = 2;
// 	cmd_node5.cmd = ft_split("tail -n 1", ' ');
// 	cmd_node5.next = NULL;
// 	cmd_node5.file_list = &file_list5;
// 	file_list5.head = NULL;
// 	file_list5.tail = NULL;
// 	file_list5.size = 0;
// 	ft_execute(&cmd_list, envp);
// 	return (0);
// }

//test for multiple in and out
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_node	file_node1;
// 	t_file_node file_node2;
// 	t_file_node file_node3;
// 	t_file_node file_node4;
// 	t_file_node	file_node5;
// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node2;
// 	cmd_list.size = 2;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 1", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 4;
// 	file_node1.redir_type = 1;
// 	file_node1.filename = "test";
// 	file_node1.next = &file_node2;
// 	file_node2.filename = "ausgabe";
// 	file_node2.redir_type = 2;
// 	file_node2.next = &file_node3;
// 	file_node3.filename = "eingabe";
// 	file_node3.redir_type = 1;
// 	file_node3.next = &file_node4;
// 	file_node4.filename = "ausgabe2";
// 	file_node4.redir_type = 2;
// 	file_node4.next = NULL;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("wc", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	cmd_node2.next = NULL;
// 	file_list2.head = NULL; //&file_node5;
// 	file_list2.size = 0;
// 	file_list2.tail = NULL;
// 	ft_execute(&cmd_list, envp);
// 	return (0);
// }