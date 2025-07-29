/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:15 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/29 15:57:19 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"
#include "executer.h"

void	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	if (cmd_node->cmd[0] == NULL)
		ft_exit_and_close(0);
	if (cmd_node->cmd[0][0] == '/')
		get_bash()->path = cmd_node->cmd[0];
	else if (ft_strncmp("./", cmd_node->cmd[0], 2) == 0)
		get_bash()->path = ft_execute_local(cmd_node->cmd[0], envp);
	else
		get_bash()->path = ft_getpath(cmd_node->cmd[0], envp);
	if (get_bash()->path == NULL)
	{
		perror("shell ");
		ft_exit_and_close(127);
	}
	execve(get_bash()->path, cmd_node->cmd, envp);
	perror("shell ");
	if (errno == EACCES)
		ft_exit_and_close(126);
	else
		ft_exit_and_close(127);
}

void	manage_single_cmd_node(
	t_cmd_list *cmd_list, t_cmd_node *cmd_node, char **envp)
{
	int		backup_stdout;
	int		backup_stdin;

	if ((cmd_list->head->cmd[0] != NULL && ft_strcmp("exit",
				cmd_list->head->cmd[0]) == false)
		|| cmd_list->head->cmd[0] == NULL)
	{
		backup_stdout = dup(STDOUT_FILENO);
		backup_stdin = dup(STDIN_FILENO);
	}
	if (ft_manage_redirections_multi(cmd_node->file_list) == false)
	{
		get_exit_codes()->last_exit_code = 1;
		return ;
	}
	ft_execute_builtin(cmd_list, cmd_node, envp);
	reset_redir(&backup_stdin, &backup_stdout);
}

void	execution_node(t_cmd_list *cmd_list,
	t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	reset_sig_handler_to_child();
	if (cmd_list->size > 1)
	{
		if (ft_manage_pipes(cmd_list, cmd_node, fd) == false)
			ft_exit_and_close(1);
	}
	if (ft_manage_redirections_multi(cmd_node->file_list) == false)
		ft_exit_and_close(1);
	if (cmd_node->cmd_type == EXECUTE)
		ft_execute_command(cmd_node, envp);
	else if (cmd_node->cmd_type == BUILTIN)
	{
		ft_execute_builtin(cmd_list, cmd_node, envp);
		ft_exit_and_close(get_exit_codes()->last_exit_code);
	}
}

void	ft_execution_loop(t_cmd_list *cmd_list, char **envp, int (*fd)[2])
{
	int			pid;
	int			i;
	t_cmd_node	*cur_cmd_node;

	i = 0;
	cur_cmd_node = cmd_list->head;
	while (cur_cmd_node != NULL)
	{
		pid = fork();
		if (pid == 0)
			execution_node(cmd_list, cur_cmd_node, fd, envp);
		free(get_bash()->path);
		get_bash()->path = NULL;
		cur_cmd_node = cur_cmd_node->next;
		if (i < cmd_list->size - 1)
			close(fd[i][1]);
		if (i > 0 && i < cmd_list->size - 1)
			close(fd[i - 1][0]);
		i++;
	}
	ft_wait_for_all(pid, cmd_list);
	close_pipe_and_free_fd(fd, i, cmd_list->size);
}

void	ft_execute(t_cmd_list *cmd_list, char **envp)
{
	int		(*fd)[2];

	set_heredoc_cmd_list(cmd_list);
	save_heredoc_files(&cmd_list->head);
	if (create_pipes(&fd, cmd_list) != true)
		return ;
	if (cmd_list->size == 1 && cmd_list->head->cmd_type == BUILTIN)
		manage_single_cmd_node(cmd_list, cmd_list->head, envp);
	else
		ft_execution_loop(cmd_list, envp, fd);
	clean_cmd_lst(cmd_list);
}

// int max_fd = sysconf(_SC_OPEN_MAX);  // Get maximum possible FDs
// printf("Open file descriptors:\n");
// for (int fd = 0; fd < max_fd; ++fd) {
// 	if (fcntl(fd, F_GETFD) != -1) {  // If fcntl doesn't return error,
// fd is open
// 		printf("FD %d is open\n", fd);
// 	}
// }