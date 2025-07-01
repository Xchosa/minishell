/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_discriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:35:55 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/01 11:01:21 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executer.h"


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