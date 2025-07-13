/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:43 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/07 15:30:58 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_cmd_list	*cmd_list_to_null(void)
{
	t_cmd_list	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	return (cmd_list);
}

t_file_list	*file_list_to_null(void)
{
	t_file_list	*file_list;

	file_list = malloc(sizeof(t_file_list));
	if (!file_list)
		return (NULL);
	file_list->head = NULL;
	file_list->tail = NULL;
	file_list->size = 0;
	return (file_list);
}

t_cmd_node	*init_cmd_node_null(t_file_list *file_list)
{
	t_cmd_node 	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->file_list = file_list;
	cmd_node->next = NULL;
	cmd_node->cmd_type = 0;
	return (cmd_node);
}

t_cmd_list	*init_cmd_list(t_token **token_list, char *original_line)
{
	t_cmd_list	*cmd_list;
	t_cmd_node	*cmd_node;
	(void)original_line;

	cmd_list = cmd_list_to_null();
	while ((*token_list))
	{
		if (cmd_list->head == NULL)
		{
			cmd_list->head = process_token(token_list);
			cmd_node = cmd_list->head;
			cmd_list->tail = cmd_node;
			cmd_list->size += 1;
		}
		else
		{
			cmd_node->next = process_token(token_list);
			cmd_node = cmd_node->next;
			cmd_list->tail = cmd_node;
			cmd_list->size += 1;
		}
	}
	return (cmd_list);
}
