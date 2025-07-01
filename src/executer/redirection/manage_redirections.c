/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:58:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:59 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


// void	ft_manage_redirections
// 	(t_cmd_node *cmd_node, int fd[][2], int backupStdin, int backupStdout)
// {
// 	t_file_node	*current;

// 	(void) backupStdin;
// 	(void) backupStdout;
// 	current = cmd_node->file_list->head;
// 	while (current != NULL)
// 	{
// 		if (current->redir_type == REDIRECT_INPUT)
// 			ft_manage_infile(current->filename, fd);
// 		else if (current->redir_type == HERE_DOC)
// 		{
// 			ft_manage_heredoc(current->filename, fd);// 
// 		}
// 		else if (current->redir_type == REDIRECT_OUTPUT)
// 			ft_manage_outfile(current->filename, fd);
// 		else if (current->redir_type == APPEND)
// 			ft_manage_append(current->filename, fd);
// 		current = current->next;
// 	}
// }

// need to be changed to bool 
bool	ft_manage_redirections_multi
	(t_file_list *file_list, int fd[][2], int backupStdin, int backupStdout)
{
	t_file_node	*cur_file_node;
	int check;
	
	check = true;
	if(!file_list)
		return 0;
	(void) backupStdout;
	(void) backupStdin;
	
	cur_file_node = file_list->head;
	while (cur_file_node != NULL)
	{
		if (cur_file_node->redir_type == REDIRECT_INPUT)
			check = ft_manage_infile(cur_file_node->filename, fd);
		else if (cur_file_node->redir_type == HERE_DOC)
			check = ft_manage_heredoc(cur_file_node->filename, fd);
			// ft_manage_heredoc(current->filename, fd);// 
		else if (cur_file_node->redir_type == REDIRECT_OUTPUT)
			check = ft_manage_outfile(cur_file_node->filename, fd);
		else if (cur_file_node->redir_type == APPEND)
			check = ft_manage_append(cur_file_node->filename, fd);
		
		if (check == false)
			return false;
		cur_file_node = cur_file_node->next;
	}
	return true;
}




// Return 0 for success
// Return specific error codes (non-zero) for different failures
