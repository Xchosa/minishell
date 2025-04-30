/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:57:58 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/30 11:32:44 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	print_cmd_lst(t_cmd_list *cmd_lst)
{
	int i;

	i = 0;
	printf(" cmd node type head: %d \n" , cmd_lst->head->cmd_type );
	printf("cmd node char arry: \n");
	while(cmd_lst->head->cmd[i])
	{
		printf("%d. %s | ", i, cmd_lst->head->cmd[i]);
		i++;
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
