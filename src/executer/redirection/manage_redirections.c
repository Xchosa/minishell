


#include "executer.h"


void	ft_manage_redirections(t_cmd_node *cmd_node, int fd[][2])
{
	t_file_node	*current;

	
	current = cmd_node->file_list->head;
	while (current != NULL)
	{
		if (current->redir_type == REDIRECT_INPUT)
			ft_manage_infile(current->filename, fd);
		else if (current->redir_type == REDIRECT_OUTPUT)
			ft_manage_outfile(current->filename, fd);
		else if (current->redir_type == HERE_DOC)
			ft_manage_heredoc(current->filename, fd);// 
		else if (current->redir_type == APPEND)
			ft_manage_append(current->filename, fd);
		current = current->next;
	}
}



// int manage_single_cmd_node(cmd_list, cur_cmd_node, fd, envp)
// {
// 	int backupStdout = dup(STDOUT_FILENO);
// 	int backupStdin = dup(STDIN_FILENO);

// 	// manage redirections

// 	// redirecte Stdout_filien, zuruck auf backupSTDout
// 	dup2(backupStdout, STDOUT_FILENO);
// }



