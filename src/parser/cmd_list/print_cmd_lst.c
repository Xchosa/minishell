/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:57:58 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/05 16:11:53 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	print_cmd_lst(t_cmd_node *cmd_nodes)
{
	int i;
	t_file_node *current_file_node;
	i = 0;
	printf(" cmd node type head: %d \n" , cmd_nodes->cmd_type );
	printf("cmd node char arry: \n");
	while(cmd_nodes->cmd[i])
	{
		printf("%d. %s | ", i, cmd_nodes->cmd[i]);
		i++;
	}
	current_file_node = cmd_nodes->file_list->head;
	printf("file node: \n");
	while(current_file_node->next)
	{
		printf("redir_typ: %d |", current_file_node->redir_type);
		printf("filename: %s |\n", current_file_node->filename);
	}
	
	// next zu file list 
}

void	iter_cmdlst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*))
{
	if (cmd_lst == NULL)
		return ;
	t_cmd_node *current_node;
	current_node = cmd_lst->head;
	while (current_node->next != NULL)
	{
		f(current_node);
		current_node = current_node->next;
	}
	return ;
}
