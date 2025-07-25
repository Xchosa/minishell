/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:15 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/25 15:29:57 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"
#include "executer.h"

void	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	if (cmd_node->cmd[0] == NULL)
		exit (0);
	if (cmd_node->cmd[0][0] == '/')
	{
		get_bash()->path = cmd_node->cmd[0]; //hier andere fehlermeldung aber gleicher code
		// if (access(get_bash()->path, X_OK) != 0)
		// 	get_bash()->path = NULL;
	}
	else if (ft_strncmp("./", cmd_node->cmd[0], 2) == 0)
		get_bash()->path = ft_execute_local(cmd_node->cmd[0], envp); //hier andere fehlermeldung aber gleicher code
	else
		get_bash()->path = ft_getpath(cmd_node->cmd[0], envp);
	if (get_bash()->path == NULL)
	{
		perror("shell ");
	 	//ft_putendl_fd("Shell: command not found\n", 2); // 2 exit codes bze fehlermeldunge, command not found und not a file or directory, ./bla /bla und bla und . und ..
	 	exit(127);
	}
	execve(get_bash()->path, cmd_node->cmd, envp);
	perror("shell ");
	if (errno ==  EACCES)
		exit (126);
	else
		exit (127);
}

void	manage_single_cmd_node(t_cmd_list *cmd_list, t_cmd_node *cmd_node, char **envp)
{
	if (ft_manage_redirections_multi(cmd_node->file_list) == false)
	{
		get_exit_codes()->last_exit_code = 1;
		return ;
	}
	ft_execute_builtin(cmd_list, cmd_node, envp);
}

void	execution_node(t_cmd_list *cmd_list,
	t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	reset_sig_handler_to_child(); // test
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
		ft_execute_builtin(cmd_list, cmd_node, envp);
		exit (get_exit_codes()->last_exit_code);
	}
}

void	ft_wait_for_all(int pid, t_cmd_list *cmd_list)
{
	int	status;
	int	i;

	i = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_exit_codes()->last_exit_code = WEXITSTATUS(status);
	while (i < cmd_list->size - 1)
	{
		//wait(NULL);
		i++;
	}
	// for (int j = 0; j < cmd_list->size - 1; j++)
	// 	wait(NULL);
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
		//wait(&status);
		free(get_bash()->path);
		get_bash()->path = NULL;
		// if (WIFEXITED(status))
		// 	get_exit_codes()->last_exit_code = WEXITSTATUS(status);
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
	int		backup_stdout;
	int		backup_stdin;
	int		(*fd)[2];

	backup_stdout = dup(STDOUT_FILENO);
	backup_stdin = dup(STDIN_FILENO);
	set_heredoc_cmd_list(cmd_list);
	save_heredoc_files(&cmd_list->head);
	if (create_pipes(&fd, cmd_list) != true)
		return ;
	//iter_cmd_lst(cmd_list, &print_cmd_lst);
	//iter_cmd_lst(cmd_list, &print_cmd_lst);
	if (cmd_list->size == 1 && cmd_list->head->cmd_type == BUILTIN)
		manage_single_cmd_node(cmd_list, cmd_list->head, envp);
	else
		ft_execution_loop(cmd_list, envp, fd);
	reset_redir(&backup_stdin, &backup_stdout);
	clean_cmd_lst(cmd_list);
	// int leaked = 0;
	// for (int i = 3; i < 1024; ++i) {
	// 	if (fcntl(i, F_GETFD) != -1) {
	// 		printf("FD %d is still open\n", i);
	// 		leaked++;
	// 	}
	// }
	// if (leaked == 0)
	// 	printf("🎉 All file descriptors properly closed!\n");
}

// echo ?! -> should return a new line 
// cmd list => uebergibt 'echo' '' -> besser NULL?
// <<hello <<now funcitioniert
// echo hallo <<now 		->printed nicht hallo nach heredoc
// cat <<now 				haegt sich auf 
// how to close all pipes if error e.g infile not exisiting
// void	ft_close_and_free(int (*fd)[2], int count, int size)
// {
// 	int j;

// 	j = 0;
// 	if (size > 1 && count == size)
// 	{
// 		close(fd[count - 2][0]);
// 		printf("closed a 0 from %d from arsch!! \n", count - 2);
// 	}
// 	else
// 	{
// 		close(fd[count - 1][0]);
// 		printf("closed a 0 from %d from arsch!! \n", count - 1);
// 	}
// 	while (count < size)
// 	{
// 		close(fd[count][0]);
// 		printf("closed a 0 from %d!! in close function\n", count);
// 		close(fd[count][1]);
// 		printf("closed a 1 from %d!! in close funtion\n", count);
// 		count++;
// 	}
// 	free(fd);
// }
// void	ft_execution_loop(t_cmd_list *cmd_list, char **envp)
// {
// 	int			status;
// 	int			pid;
// 	int			i;
// 	t_cmd_node	*cur_cmd_node;
// 	int			(*fd)[2];

// 	i = 0;
// 	fd = malloc(sizeof(int [2]) * cmd_list->size);
// 	cur_cmd_node = cmd_list->head;
// 	if (cmd_list->size > 1)
// 		ft_open_pipes(fd, cmd_list); //eigentlich nur dann malloc, etl malloc mit in die f packen
// 	while ((cur_cmd_node != NULL) && (i < 1 || get_exit_codes()->last_exit_code == 0))
// 	{
// 		pid = fork();
// 		if (pid == 0) //hier ENV updaten?????????? oder auch nicht bash packt auch kein pipe nach unset zB
// 			execution_node(cmd_list, cur_cmd_node, fd, envp);
// 		wait(&status);
// 		if (WIFEXITED(status))
// 			get_exit_codes()->last_exit_code = WEXITSTATUS(status);
// 		cur_cmd_node = cur_cmd_node->next;
// 		if (i < cmd_list->size - 1)
// 		{
// 			close(fd[i][1]);
// 			printf("closed a 1 from %d !! \n", i);
// 		}
// 		if (i > 0 && i < cmd_list->size - 1)
// 		{
// 			close(fd[i - 1][0]);
// 			printf("closed a 0 from %d !! \n", i - 1);
// 		}
// 		i++;
// 	}
// 	ft_close_and_free(fd, i, cmd_list->size);
// }