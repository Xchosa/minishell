/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:58:15 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/23 15:54:17 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executer.h"

/*
1. iterate through every cmd node 
	each cmd note itereate through file list for heredoc
		heredoc_create ,
			save content in /tmp/ ordner -> change filname (in file_node zu int 
			und nummerier durch falls weiterer heredoc )
			(noetig falls identische heredoc namen)
				eg. <<now <<hello 
					-> 1
						->2 

2.execution der cmd node 
	e.g. cat <<now 
		file_node = type 3, filename /tmp/order/1
		
				

*/

bool check_for_interactive_shell(void)
{
	if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return true;
	return false;
}


bool execute_here_doc(char *filename, int here_doc_fd)
{
	char *line;
	while(1)
	{
		// change signal for parent heredoc
		if(check_for_interactive_shell == true)
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if(!line)
			break;
		if(strcmp(line, filename) == true)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, here_doc_fd);
		if (check_for_interactive_shell() == true)
            ft_putstr_fd("\n", fd);// for readline
		free(line);
	}
	close(fd);
	// change signal back
	return true;
}


void save_here_doc_in_tmp(t_file_node **file_node)
{
	int		here_doc_fd;
	char	*new_tmp_file_name;
	
	
	// without changing name (so same named heredoc can be distinguished)
	new_tmp_file_name = ft_strjoin("tmp/.here_doc_",(*file_node)->filename);
	
	here_doc_fd = open(new_tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return (ft_putstr_fd("Operation not permitted\n", 2), NULL);
	if(execute_here_doc((*file_node)->filename, here_doc_fd))
	{
		close(here_doc_fd);
		return ;
	}
	free((*file_node)->filename);
	(*file_node)->filename = new_tmp_file_name;
}




void find_here_doc_file_node(t_file_node **file_node)
{
	while(*file_node)
	{
		if((*file_node)->redir_type == HERE_DOC)
		{
			save_here_doc_in_tmp((*file_node));
		}
		(*file_node)= (*file_node)->next;
	}
}



// head uebergeben // muss doppelpointer sein um die nodes zu veraendern
void save_heredoc_files(t_cmd_node **cmd_node)
{	
	while(cmd_node)
	{
		if((*cmd_node)->file_list)
		{
			find_here_doc_file_node((*cmd_node)->(*file_list)->head);
		}
		// is cmd_node am ende immer NULL? 
		if((*cmd_node)->next != NULL)
			(*cmd_node) = (*cmd_node)->next;
		else 
			break;
	}

}

