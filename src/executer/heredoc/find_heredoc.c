/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:58:15 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/22 15:05:15 by poverbec         ###   ########.fr       */
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

static int	error_heredoc(char *new_tmp_file_name_suffix,
	char *new_tmp_file_name, char *suffix)
{
	free(new_tmp_file_name_suffix);
	free(suffix);
	free(new_tmp_file_name);
	perror("open failed");
	ft_putstr_fd("Operation not permitted\n", 2);
	return (1);
}

static	void	free_heredoc_helper(char *new_tmp_file_name,
	char *suffix, t_file_node **file_node)
{
	free(new_tmp_file_name);
	free(suffix);
	free((*file_node)->filename);
}

static	void	free_heredoc_stoped(char *new_tmp_file_name_suffix,
	char *new_tmp_file_name, char *suffix)
{
	free(new_tmp_file_name_suffix);
	free(new_tmp_file_name);
	free(suffix);
}

bool	check_for_interactive_shell(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (true);
	return (false);
}





int	save_here_doc_in_tmp(t_file_node **file_node)
{
	int			here_doc_fd;
	char		*new_tmp_file_name;
	char		*n_t_file_name_suf;
	char		*suffix;
	static int	count = 0;

	suffix = ft_itoa(count);
	count++;
	new_tmp_file_name = ft_strjoin("/tmp/.here_doc_", (*file_node)->filename);
	change_filename(new_tmp_file_name);
	n_t_file_name_suf = ft_strjoin(new_tmp_file_name, suffix);
	here_doc_fd = open(n_t_file_name_suf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return (error_heredoc(n_t_file_name_suf, new_tmp_file_name, suffix), 1);
	if (execute_here_doc((*file_node)->filename, here_doc_fd) == false)
	{
		unlink(n_t_file_name_suf);
		free_heredoc_stoped(n_t_file_name_suf, new_tmp_file_name, suffix);
		return (1);
	}
	free_heredoc_helper(new_tmp_file_name, suffix, file_node);
	(*file_node)->filename = n_t_file_name_suf;
	return (0);
}
