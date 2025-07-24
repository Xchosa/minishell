/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_cmd_file_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:58:57 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/24 14:45:23 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "signal_tp.h"

int	find_here_doc_file_node(t_file_node **file_node)
{
	t_file_node	*cur_file_node;

	cur_file_node = *file_node;
	while (cur_file_node)
	{
		if (cur_file_node->redir_type == HERE_DOC)
		{
			if (save_here_doc_in_tmp(&cur_file_node) != 0)
				return (1);
		}
		if (cur_file_node->next)
			cur_file_node = cur_file_node->next;
		else
			return (0);
	}
	return (0);
}

void	save_heredoc_files(t_cmd_node **cmd_node)
{
	t_cmd_node	*cur_cmd_node;

	cur_cmd_node = *cmd_node;
	while (cur_cmd_node)
	{
		if (cur_cmd_node->file_list && cur_cmd_node->file_list->head)
		{
			if (find_here_doc_file_node(&cur_cmd_node->file_list->head) != 0)
				return ;
		}
		cur_cmd_node = cur_cmd_node->next;
	}
}

// void change_incorrect_file_name