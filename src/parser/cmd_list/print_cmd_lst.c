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
	int j;
	j = 1;
	i = 0;
	printf("\ndo i come here too 2:\n\n");
	printf(" cmd node type head: %d \n" , cmd_nodes->cmd_type );
	printf("cmd node char arry: \n");
	while(cmd_nodes->cmd[i])
	{
		printf("%d. %s | ", i, cmd_nodes->cmd[i]);
		i++;
	}
	printf("\n");
	if(cmd_nodes->file_list != NULL && cmd_nodes->file_list->head != NULL)
	{	
		printf("file node head redir type: %d\n", cmd_nodes->file_list->head->redir_type);
		printf("file node head filname: %s\n ", cmd_nodes->file_list->head->filename);
		t_file_node *current_tail = cmd_nodes->file_list->head->next;
        
        while(current_tail != NULL)
        {
            printf("file node tail %d redir type: %d\n", j, current_tail->redir_type);
            printf("file node tail %d filename: %s\n ", j, current_tail->filename);
            j++;
            current_tail = current_tail->next;
        }
	}
	// next zu file list 
}

void	iter_cmd_lst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*))
{
	if (cmd_lst == NULL)
		return ;
	t_cmd_node *current_node;
	current_node = cmd_lst->head;
	printf("\ndo i come here too 1:\n\n");
	while (current_node)
	{
		f(current_node);
		current_node = current_node->next;
		printf("\n");
	}
	return ;
}
