/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:58:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/30 14:46:16 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


void	ft_manage_redirections
	(t_cmd_node *cmd_node, int fd[][2], int backupStdin, int backupStdout)
{
	t_file_node	*current;

	(void) backupStdin;
	(void) backupStdout;
	current = cmd_node->file_list->head;
	while (current != NULL)
	{
		if (current->redir_type == REDIRECT_INPUT)
			ft_manage_infile(current->filename, fd);
		else if (current->redir_type == HERE_DOC)
		{
			ft_manage_heredoc(current->filename, fd);// 
		}
		else if (current->redir_type == REDIRECT_OUTPUT)
			ft_manage_outfile(current->filename, fd);
		else if (current->redir_type == APPEND)
			ft_manage_append(current->filename, fd);
		current = current->next;
	}
}



void	reset_redir(int *backupStdin, int *backupStdout)
{
	// dup2(*backupStdin, STDIN_FILENO);
	// dup2(*backupStdout, STDOUT_FILENO);
	// close(*backupStdin);
	// close(*backupStdout);

	if (*backupStdin != -1)
    {
        dup2(*backupStdin, STDIN_FILENO); // Restore stdin
        close(*backupStdin);             // Close the backup
        *backupStdin = -1;               // Mark as invalid
    }
    if (*backupStdout != -1)
    {
        dup2(*backupStdout, STDOUT_FILENO); // Restore stdout
        close(*backupStdout);               // Close the backup
        *backupStdout = -1;                 // Mark as invalid
    }
}

// void set_up_backup_Stdout_Stdin(int *backupStdin, int *backupStdout)
// {
// 	// backupStdin = 0;
// 	// backupStdout = 0;
// 	*backupStdout = dup(STDOUT_FILENO);
//     *backupStdin = dup(STDIN_FILENO);
// }

void	ft_manage_redirections_multi
	(t_cmd_node *cmd_node, int fd[][2], int backupStdin, int backupStdout)
{
	t_file_node	*current;
	(void) backupStdin;
	
	current = cmd_node->file_list->head;
	while (current != NULL)
	{
		if (current->redir_type == REDIRECT_INPUT)
			ft_manage_infile(current->filename, fd);
		else if (current->redir_type == HERE_DOC)
			ft_manage_heredoc_stdout(current->filename, fd, backupStdout);
			// ft_manage_heredoc(current->filename, fd);// 
		else if (current->redir_type == REDIRECT_OUTPUT)
			ft_manage_outfile(current->filename, fd);
		else if (current->redir_type == APPEND)
			ft_manage_append(current->filename, fd);
		current = current->next;
	}
}



