/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:43 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 12:57:07 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_cmd_list *cmd_list_to_NULL(void)
{
	t_cmd_list *cmd_list;

	cmd_list = malloc(sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	return(cmd_list);
}

t_file_list *file_list_to_NULL(void)
{
	t_file_list *file_list;

    file_list = malloc(sizeof(t_file_list));
	if (!file_list)
		return (NULL);
    file_list->head = NULL;
    file_list->tail = NULL;
    file_list->size = 0;
    return  (file_list);
}

t_cmd_list	*init_cmd_list(t_token **token_list,char *line)
{
	t_cmd_list *cmd_list;
	t_cmd_node 	*cmd_node;

	cmd_list = cmd_list_to_NULL();
	while((*token_list))
	{
		if(cmd_list->head == NULL)
		{
			cmd_list->head = process_token(token_list);
			cmd_node = cmd_list->head;
			cmd_list->tail = cmd_node;
			cmd_list->size +=1;
		}
		else
		{
			cmd_node->next = process_token(token_list);
			cmd_node = cmd_node->next;
			cmd_list->tail = cmd_node;
			cmd_list->size +=1;
		}
	}
	clean_token_lst_and_line((*token_list),line);
	return(cmd_list);
}
