#include "../../inc/executer.h"

ft_open_pipes(int **i)
{
	
}


void	ft_execute_node(t_cmd_node	*cmd_node)
{
	
}

void	ft_execute(t_cmd_list *cmd_list)
{
	t_cmd_node	*current;
	int pid;
	int fd[cmd_list->size][2];

	if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
		return ; // sonderfall ohne fork; warum?
	current = cmd_list->head;
	if (cmd_list->size > 1)
	ft_open_pipes(fd);
	while (current != NULL)
	{
		pid = fork();
		if (pid == 0)
			ft_execute_node(current);
		else
			wait;
		current = current->next;
	}
}

int	main()
{
	t_cmd_list	cmd_list;
	t_cmd_node	cmd_node1;
	t_file_list	file_list;
	t_file_node	file_node1;

	cmd_list.head = &cmd_node1;
	cmd_list.tail = NULL;
	cmd_list.size = 1;
	cmd_node1.cmd_type = 2;
	cmd_node1.cmd = ft_split("cat", ' ');
	cmd_node1.file_list = &file_list;
	cmd_node1.next = NULL;
	file_list.head = &file_node1;
	file_list.tail = NULL;
	file_list.size = 1;
	file_node1.redir_type = 0;
	file_node1.filename = "test";
	file_node1.next = NULL;
	ft_execute(&cmd_list);
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