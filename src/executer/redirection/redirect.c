/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:52 by tschulle          #+#    #+#             */
/*   Updated: 2025/06/25 14:44:13 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_manage_infile(char *infile, int fd[][2])
{
	int	in_fd;
	(void)fd;
	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
		return ;
	if (dup2(in_fd, STDIN_FILENO) < 0)
		return ;
	close (in_fd);
	return ;
}

void	ft_manage_outfile(char *outfile, int fd[][2])
{
	int	out_fd;
	(void)fd;
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd < 0)
		return ;
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		return ;
	close (out_fd);
	return ;
}

void	ft_manage_append(char *appendfile, int fd[][2])
{
	int	ap_fd;
	(void)fd;
	ap_fd = open(appendfile, O_WRONLY | O_APPEND | O_CREAT);
	if (ap_fd < 0)
		return ;
	if (dup2(ap_fd, STDOUT_FILENO) < 0)
		return ;
	close(ap_fd);
	return ;
}


// complett neu 
/// only prints out to console 
void	ft_manage_heredoc(char *tmp_filename, int fd[][2])
{
	int here_doc_fd;
	(void)fd;
	here_doc_fd = open(tmp_filename, O_RDONLY);
	if(here_doc < 0)
		return;
	if(dup2(here_doc_fd , STDOUT_FILENO) < 0)
		return;
	close(here_doc_fd);
	// eigentlichen stdout zurucksetzen,
	// heaengt sich auf bei cat <<now
	// muss nur noc /tmp/filename aufrufen -> in der fertig bereits
	// ausgefuehrter und gespeicherterte heredoc ist
//	z.B. cat <<now
}


