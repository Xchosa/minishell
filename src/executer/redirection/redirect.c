/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:52 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/21 10:46:55 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

bool	ft_manage_infile(char *infile)
{
	int	in_fd;

	in_fd = open(infile, O_RDONLY);
	if (in_fd < 0)
	{
		ft_putstr_fd(" Infile not existing\n", STDERR_FILENO);
		return (false);
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDERR_FILENO);
		close (in_fd); //new
		return (false);
	}
	close (in_fd);
	return (true);
}

bool	ft_manage_outfile(char *outfile)
{
	int	out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd < 0)
		return (false);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		close (out_fd);
		return (false);
	}
	close (out_fd);
	return (true);
}

bool	ft_manage_append(char *appendfile)
{
	int	ap_fd;

	ap_fd = open(appendfile, O_WRONLY | O_APPEND | O_CREAT);
	if (ap_fd < 0)
	{
		ft_putstr_fd("creating appendfile failed\n", STDERR_FILENO);
		return (false);
	}
	if (dup2(ap_fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDERR_FILENO);
		close (ap_fd);
		return (false);
	}
	close(ap_fd);
	return (true);
}

bool	ft_manage_heredoc(char *tmp_filename)
{
	int	here_doc_fd;

	here_doc_fd = open(tmp_filename, O_RDONLY);
	if (here_doc_fd < 0)
	{
		printf("could not open heredoc\n");
		return (false);
	}
	if (dup2(here_doc_fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd(" redirecting failed\n", STDERR_FILENO);
		close (here_doc_fd);
		return (false);
	}
	else
	{
		close(here_doc_fd);
		return (true);
	}
}
