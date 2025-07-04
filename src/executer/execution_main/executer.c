/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:15 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/04 19:00:00 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	path = ft_getpath(cmd_node->cmd[0], envp);
	if (path == NULL)
	{
		ft_putendl_fd("Shell: command not found\n", 2);
		exit(127);
	}
	execve(path, cmd_node->cmd, envp);
	perror("Execve failed");
	exit(errno);
}

void	manage_single_cmd_node(t_cmd_node *cmd_node, char **envp)
{
	if (ft_manage_redirections_multi(cmd_node->file_list))
		get_exit_codes()->last_exit_code = 1;
	ft_execute_builtin(cmd_node, envp);
}

void	execution_node(t_cmd_list *cmd_list,
	t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	if (cmd_list->size > 1)
	{
		if (ft_manage_pipes(cmd_list, cmd_node, fd) == false)
			exit(1);
	}
	if (ft_manage_redirections_multi(cmd_node->file_list) == false)
		exit(1);
	if (cmd_node->cmd_type == EXECUTE)
		ft_execute_command(cmd_node, envp);
	else if (cmd_node->cmd_type == BUILTIN)
	{
		ft_execute_builtin(cmd_node, envp);
		exit (get_exit_codes()->last_exit_code);
	}
}

void	ft_execution_loop(t_cmd_list *cmd_list, char **envp)
{
	int			status;
	int			pid;
	int			i;
	t_cmd_node	*cur_cmd_node;
	int			(*fd)[2];

	i = 0;
	fd = malloc(sizeof(int [2]) * cmd_list->size);
	cur_cmd_node = cmd_list->head;
	if (cmd_list->size > 1)
		ft_open_pipes(fd, cmd_list); //eigentlich nur dann malloc, etl malloc mit in die f packen
	while ((cur_cmd_node != NULL) && (i < 1 || get_exit_codes()->last_exit_code == 0))
	{
		pid = fork();
		if (pid == 0)
			execution_node(cmd_list, cur_cmd_node, fd, envp);
		wait(&status);
		if (WIFEXITED(status))
			get_exit_codes()->last_exit_code = WEXITSTATUS(status);
		cur_cmd_node = cur_cmd_node->next;
		if (i < cmd_list->size - 1)
			close(fd[i][1]);
		if (i > 0 && i < cmd_list->size - 1)
			close(fd[i - 1][0]);
		i++;
	}
	if (cmd_list->size > 1)
		close(fd[i - 1][0]);
	//ft_close_and_free_clean
}

void	ft_execute(t_cmd_list *cmd_list, char **envp)
{
	int	backup_stdout;
	int	backup_stdin;

	backup_stdout = dup(STDOUT_FILENO);
	backup_stdin = dup(STDIN_FILENO);
	save_heredoc_files(&cmd_list->head);
	iter_cmd_lst(cmd_list, &print_cmd_lst);
	if (cmd_list->size == 1 && cmd_list->head->cmd_type == BUILTIN)
		manage_single_cmd_node(cmd_list->head, envp);
	else if (ft_strcmp("./minishell", cmd_list->head->cmd[0]) == true)
		ft_minishell_nested(envp);
	else
		ft_execution_loop(cmd_list, envp);
	reset_redir(&backup_stdin, &backup_stdout);
	//clean_cmd_list_objects_tmp_files(cmd_list);
}

// echo ?! -> should return a new line 
// cmd list => uebergibt 'echo' '' -> besser NULL?
// <<hello <<now funcitioniert
// echo hallo <<now 		->printed nicht hallo nach heredoc
// cat <<now 				haegt sich auf 
// how to close all pipes if error e.g infile not exisiting