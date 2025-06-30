/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:58:15 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/30 15:42:37 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "signal_tp.h"

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
		
				
// status quo 


*/


static int error_heredoc(char *new_tmp_file_name_suffix,char *new_tmp_file_name,char *suffix)
{
	free(new_tmp_file_name_suffix);
	free(suffix);
	free(new_tmp_file_name);
	perror("open failed");
	ft_putstr_fd("Operation not permitted\n", 2);
	return 1;
}
static void free_heredoc_helper(char *new_tmp_file_name,char *suffix, t_file_node **file_node)
{
	free(new_tmp_file_name);
	free(suffix);
	free((*file_node)->filename);
}

static void free_heredoc_stoped(char *new_tmp_file_name_suffix,char *new_tmp_file_name, char* suffix)
{
 	free(new_tmp_file_name_suffix);
    free(new_tmp_file_name);
    free(suffix);
}

bool check_for_interactive_shell(void)
{
	if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return true;
	return false;
}

// reset handlers and change signal for parent process
bool execute_here_doc(char *filename, int here_doc_fd)
{
	char *line;
	while(1)
	{
		reset_sig_handler_to_parent();
		if(check_for_interactive_shell () == true)
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if(!line)
			break;
		skip_whitespace(&line);
		if(ft_strcmp(line, filename) == true)
		{
			free(line);
			close(here_doc_fd);// doppelt
			init_signal(1);
			return(true);
		}
		ft_putstr_fd(line, here_doc_fd);
		if (check_for_interactive_shell() == true)
            ft_putstr_fd("\n", here_doc_fd);
		free(line);
	}
	close(here_doc_fd);
	init_signal(1);
	return true;
}

// filename for tmp only allows alnum and _ -> needs to be changed to this format 
// everything else will be _ 
int save_here_doc_in_tmp(t_file_node **file_node)
{
	int			here_doc_fd;
	char		*new_tmp_file_name;
	char		*new_tmp_file_name_suffix;
	char		*suffix;
	static int	count = 0;
	
	suffix = ft_itoa(count);
	count++;
	new_tmp_file_name = ft_strjoin("/tmp/.here_doc_",(*file_node)->filename);
	new_tmp_file_name_suffix = ft_strjoin(new_tmp_file_name, suffix);
	here_doc_fd = open(new_tmp_file_name_suffix, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return(error_heredoc(new_tmp_file_name_suffix,new_tmp_file_name,suffix),1);
	if(execute_here_doc((*file_node)->filename, here_doc_fd) == false)
	{
        unlink(new_tmp_file_name_suffix);
        free_heredoc_stoped(new_tmp_file_name_suffix,new_tmp_file_name,suffix);
        return(1);
	}
	free_heredoc_helper(new_tmp_file_name, suffix, file_node);
	(*file_node)->filename = new_tmp_file_name_suffix;
	return (0);
}






