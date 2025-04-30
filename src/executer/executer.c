#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include <stdio.h>























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