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


void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_execute_builtin(t_cmd_node *cmd_node)
{
	(void) cmd_node;
	ft_printf("i am in builtin execution");
}

char	*ft_give_pointer_to_path(char **envp)
{
	int		i;
	char	*to_path;

	i = 0;
	to_path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			to_path = envp[i];
		i++;
	}
	if (to_path == NULL)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		to_path++;
		i++;
	}
	return (to_path);
}

char	*ft_getpath(char *command, char **envp)
{
	char	*to_path;
	int		i;
	char	**arr;
	char	*tmp;
	char	*full;

	to_path = ft_give_pointer_to_path(envp);
	if (to_path == NULL)
		return (NULL);
	i = 0;
	arr = ft_split(to_path, ':');
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		tmp = ft_strjoin(arr[i], "/");
		full = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (ft_free_array(arr), full);
		i++;
		free(full);
	}
	return (ft_free_array(arr), NULL);
}

void 	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	char *path;
	path = ft_getpath(cmd_node->cmd[0], envp);
	if (path == NULL)
		return ; //error free exit
	execve(path, cmd_node->cmd, envp); //errorcheck
}

void	ft_manage_infile(char *infile, int fd[][2])
{
	int in_fd;

	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
		return ;
	if (dup2(in_fd, STDIN_FILENO) < 0)
		return ; //exit und close
	close (in_fd);
	// ft_printf("%d\n", in_fd);
	// ft_printf("%d\n", STDIN_FILENO);
	return ;
}

void	ft_manage_outfile(char *outfile, int fd[][2])
{
	int out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd < 0)
		return ;
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		return ; //Errorhandling
	close (out_fd);
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
		current = current->next;
	}
}

void	ft_first_pipe(int fd[][2])
{
	close(fd[0][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		return;

}

void	ft_manage_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2])
{
	if (cmd_node == cmd_list->head)
		ft_first_pipe(fd);
// 	else if (cmd_node == cmd_list->tail)
// 		ft_last_pipe(fd);
// 	else
// 		ft_middle_pipe(fd);
}

void	ft_execute_node(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	// ft_printf("%s\n", cmd_node->cmd[0]);
	// ft_printf("%s\n", cmd_node->file_list->head->filename);
	ft_manage_pipes(cmd_list, cmd_node, fd);
	ft_manage_redirections(cmd_node, fd);
	if (cmd_node->cmd_type == 2)
		ft_execute_command(cmd_node, envp);
	else if(cmd_node->cmd_type == 1)
		ft_execute_builtin(cmd_node);
}

void	ft_execute(t_cmd_list *cmd_list,char **envp)
{
	t_cmd_node	*current;
	int pid;
	int fd[(int)cmd_list->size][2];

	// if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
	// 	return ; // sonderfall ohne fork; warum?
	current = cmd_list->head;
	if (cmd_list->size > 1)
	 	ft_open_pipes(fd, cmd_list);
	while (current != NULL)
	{
		pid = fork();
		if (pid == 0)
			ft_execute_node(cmd_list, current, fd, envp);
		else
			wait(0);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	cmd_list;
	t_cmd_node	cmd_node1;
	t_cmd_node	cmd_node2;
	t_file_list	file_list1;
	t_file_list file_list2;
	t_file_node	file_node1;
	t_file_node file_node2;
	t_file_node file_node3;
	t_file_node file_node4;
	t_file_node	file_node5;

	(void)argc;
	(void)argv;
	cmd_list.head = &cmd_node1;
	cmd_list.tail = NULL;
	cmd_list.size = 2;
	cmd_node1.cmd_type = 2;
	cmd_node1.cmd = ft_split("tail -n 1", ' ');
	cmd_node1.file_list = &file_list1;
	cmd_node1.next = &cmd_node2;
	file_list1.head = &file_node1;
	file_list1.tail = NULL;
	file_list1.size = 4;
	file_node1.redir_type = 1;
	file_node1.filename = "test";
	file_node1.next = &file_node2;
	file_node2.filename = "ausgabe";
	file_node2.redir_type = 2;
	file_node2.next = &file_node3;
	file_node3.filename = "eingabe";
	file_node3.redir_type = 1;
	file_node3.next = &file_node4;
	file_node4.filename = "ausgabe2";
	file_node4.redir_type = 2;
	file_node4.next = NULL;
	cmd_node2.cmd_type = 2;
	cmd_node2.cmd = ft_split("wc", ' ');
	cmd_node2.file_list= &file_list2;
	cmd_node2.next = NULL;
	file_list2.head = NULL; //&file_node5;
	file_list2.size = 0;
	file_list2.tail = NULL;

	
	ft_execute(&cmd_list, envp);
	return (0);
}


















// #include "../../inc/parser.h"
// #include "../../inc/minishell.h"
// #include <stdio.h>
// int	main(void)
// {
// 	t_cmd test_list;
// 	test_list.cmd_arg = ft_split("ls -la", ' ');
// 	test_list.token_type = 0;
// 	t_cmd test_list2;
// 	//test_list.next = NULL;
// 	test_list.next = &test_list2;
// 	test_list2.cmd_arg = ft_split("|", ' ');
// 	test_list2.token_type = 1;
// 	t_cmd test_list3;
// 	test_list2.next = &test_list3;
// 	test_list3.cmd_arg = ft_split("grep a1", ' ');
// 	test_list3.token_type = 0;
// 	t_cmd test_list4;
// 	test_list3.next = &test_list4;
// 	test_list4.cmd_arg = ft_split("|", ' ');
// 	test_list4.token_type = 1;
// 	t_cmd test_list5;
// 	test_list4.next = &test_list5;
// 	test_list5.cmd_arg = ft_split("wc  -l", ' ');
// 	test_list5.token_type = 0;
// 	print_ast(&test_list);
// }
// void	print_indent(t_cmd *cmds, int indent_level)
// {
// 	if (cmds->token_type == PIPE)
// 		indent_level--;
// 	while (indent_level-- > 0)
// 		printf("%s", "\t");
// }
// int	has_pipes(t_cmd *cmds)
// {
// 	int count;
// 	count = 0;
// 	while (cmds != NULL)
// 	{
// 		if (cmds->token_type == PIPE)
// 			count++;
// 		cmds = cmds->next;
// 	}
// 	return (count);
// }
// void	print_cmd(t_cmd *cmds, int indent_level)
// {
// 	int i;
// 	i = 0;
// 	print_indent(cmds, indent_level);
// 	if (cmds->cmd_arg != NULL)
// 	{
// 		while (cmds->cmd_arg[i] != 0)
// 		{
// 			printf("%s ", cmds->cmd_arg[i]);
// 			i++;
// 		}
// 	}
// 	printf("\n");
// 	print_indent(cmds, indent_level.);
// 	if (cmds->token_type != PIPE && indent_level  > 0)
// 		printf("/");
// 	else  
// 		printf("\\");
// 	printf("\n");
// }
// void	print_ast(t_cmd *cmds)
// {
// 	int level;
// 	level = has_pipes(cmds);
// 	print_cmd(cmds, level);
// 	if (cmds->next != NULL)
// 		print_ast(cmds->next);
// }