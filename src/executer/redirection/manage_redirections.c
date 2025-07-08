/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:58:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 11:33:04 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

bool	ft_manage_redirections_multi(t_file_list *file_list)
{
	t_file_node	*cur_file_node;
	int			check;

	check = true;
	if (!file_list)
		return (false);
	cur_file_node = file_list->head;
	while (cur_file_node != NULL)
	{
		if (cur_file_node->redir_type == REDIRECT_INPUT)
			check = ft_manage_infile(cur_file_node->filename);
		else if (cur_file_node->redir_type == HERE_DOC)
			check = ft_manage_heredoc(cur_file_node->filename);
		else if (cur_file_node->redir_type == REDIRECT_OUTPUT)
			check = ft_manage_outfile(cur_file_node->filename);
		else if (cur_file_node->redir_type == APPEND)
			check = ft_manage_append(cur_file_node->filename);
		if (check == false)
			return (false);
		cur_file_node = cur_file_node->next;
	}
	// for (int i = 0; i < 1024; ++i) {
	// 	if (fcntl(i, F_GETFD) != -1) {
	// 		printf("FD %d is still open\n", i);
	// 	}
	// }
	return (true);
}
