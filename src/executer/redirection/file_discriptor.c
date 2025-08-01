/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_discriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:35:55 by poverbec          #+#    #+#             */
/*   Updated: 2025/08/01 10:03:40 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	reset_redir(int *backup_stdin, int *backup_stdout)
{
	if (*backup_stdin != -1)
	{
		dup2(*backup_stdin, STDIN_FILENO);
		close(*backup_stdin);
		*backup_stdin = -1;
	}
	if (*backup_stdout != -1)
	{
		dup2(*backup_stdout, STDOUT_FILENO);
		close(*backup_stdout);
		*backup_stdout = -1;
	}
}

// int is_fd_open(int fd)
// {
//     return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
// }
// void    check_fds(void)
// {
//     int check = 0;
//     for(int i = 0; i < 21; i++)
//     {
//         check = is_fd_open(i);
//         if (i < 3)
//         {
//             ft_putstr_fd("\033[33mfd ", 2);
//             ft_putstr_fd(ft_itoa(i), 2);
//             ft_putstr_fd(" is: \033[0m", 2);
//         }
//         else
//         {
//             ft_putstr_fd("fd ", 2);
//             ft_putstr_fd(ft_itoa(i), 2);
//             ft_putstr_fd(" is: ", 2);
//         }
//         if (check == 1)
//             ft_putstr_fd("\033[32mopen\033[0m\n", 2);
//         else
//             ft_putstr_fd("\033[31mclosed\033[0m\n", 2);
//     }
// }
// dup2(*backupStdin, STDIN_FILENO);
// dup2(*backupStdout, STDOUT_FILENO);
// close(*backupStdin);
// close(*backupStdout); die unteresten 4 zeilen waren in reset_dir