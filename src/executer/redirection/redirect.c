/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:52 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/01 12:51:43 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


// use exit to terminate the child processes // bool obsolet?
// damit signaling functioniert ctrl D 

bool	ft_manage_infile(char *infile, int fd[][2])
{
	int	in_fd;
	(void)fd;
	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
	{
		ft_putstr_fd(" Infile not existing\n", STDOUT_FILENO);
		exit ; // beende den child process - forke ja immer egal(ausser 1cmd && buildin) ob es eine oder mehrere nodes sind
		return false;
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDOUT_FILENO);
		return false;
	}
	close (in_fd);
	return true;
}

bool	ft_manage_outfile(char *outfile, int fd[][2])
{
	int	out_fd;
	(void)fd;
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd < 0)
		return false ;
	// int backupIN = dup(STDOUT_FILENO);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		return false;
	close (out_fd);
	// dup2(backupIN, out_fd);
	return true;
}

bool	ft_manage_append(char *appendfile, int fd[][2])
{
	int	ap_fd;
	(void)fd;
	ap_fd = open(appendfile, O_WRONLY | O_APPEND | O_CREAT);
	if (ap_fd < 0)
	{
		ft_putstr_fd("creating Appendfile filed\n", STDOUT_FILENO);
		return false;
	}
	if (dup2(ap_fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDOUT_FILENO);
		return false;
	}
	close(ap_fd);
	return true;
}


// complett neu 
/// only prints out to console 
// void	ft_manage_heredoc(char *tmp_filename, int fd[][2])
// {
// 	int here_doc_fd;
// 	(void)fd;
// 	here_doc_fd = open(tmp_filename, O_RDONLY);
// 	if(here_doc_fd < 0)
// 		return;
// 	if(dup2(here_doc_fd , STDOUT_FILENO) < 0)
// 		return;
// 	close(here_doc_fd);
// 	// eigentlichen stdout zurucksetzen,
// 	// heaengt sich auf bei cat <<now
// 	// muss nur noc /tmp/filename aufrufen -> in der fertig bereits
// 	// ausgefuehrter und gespeicherterte heredoc ist
// //	z.B. cat <<now
// }

bool ft_manage_heredoc(char *tmp_filename, int fd[][2])
{
	int here_doc_fd;
	(void)fd;
	here_doc_fd = open(tmp_filename, O_RDONLY);
	if(here_doc_fd < 0)
	{
		printf("could not open heredoc\n");
		return false;
	}
	if(dup2(here_doc_fd , STDIN_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDOUT_FILENO);
		return false;
	}
	else
	{
		close(here_doc_fd);
		return true;
	}
}



