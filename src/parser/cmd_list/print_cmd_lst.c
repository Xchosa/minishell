/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:57:58 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/28 11:28:49 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

// void	print_cmd_lst(t_cmd_node *cmd_nodes)
// {
// 	int			i;
// 	int			j;
// 	t_file_node	*current_file_node;

// 	j = 1;
// 	i = 0;
// 	if (cmd_nodes->cmd_type == 1)
// 		printf("cmd_type: BUILTIN\n");
// 	else
// 		printf("cmd_type: EXECUTE\n");
// 	printf("cmd \n");
// 	if (cmd_nodes->cmd[i] == (void *)0)
// 		printf("NULL");
// 	else
// 	{
// 		while (cmd_nodes->cmd[i])
// 		{
// 			printf("'%s'", cmd_nodes->cmd[i]);
// 			i++;
// 		}
// 	}
// 	printf("\n");
// 	if (cmd_nodes->file_list->head != NULL)
// 	{
// 		current_file_node = cmd_nodes->file_list->head;
// 		while (current_file_node != NULL)
// 		{
// 			printf("file node tail %d redir type: %d\n", j,
// 				current_file_node->redir_type);
// 			if (current_file_node->redir_type == REDIRECT_INPUT)
// 				printf("file node tail %d redir type: redirect_Input \n", j);
// 			else if (current_file_node->redir_type == REDIRECT_OUTPUT)
// 				printf("file node tail %d redir type: redirect_Output \n", j);
// 			else if (current_file_node->redir_type == HERE_DOC)
// 				printf("file node tail %d redir type: Here_Doc \n", j);
// 			else if (current_file_node->redir_type == APPEND)
// 				printf("file node tail %d redir type: Append \n", j);
// 			printf("file node tail %d filename: %s\n ", j,
// 				current_file_node->filename);
// 			current_file_node = current_file_node->next;
// 			j++;
// 			printf("\n");
// 		}
// 	}
// }

void	iter_cmd_lst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*))
{
	t_cmd_node	*current_cmd_node;
	int			i;

	if (cmd_lst == NULL)
		return ;
	i = 1;
	current_cmd_node = cmd_lst->head;
	printf("size cmd list %ld\n", cmd_lst->size);
	while (current_cmd_node)
	{
		printf("cmd node %d\n", i);
		f(current_cmd_node);
		current_cmd_node = current_cmd_node->next;
		i++;
		printf("\n");
	}
	return ;
}

void	ft_print_array(char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		printf("%s\n", src[i]);
		i++;
	}
}
