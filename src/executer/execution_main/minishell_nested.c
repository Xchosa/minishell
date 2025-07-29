/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_nested.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:59:07 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/25 15:54:44 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "signal_tp.h"

void	ft_increase_shlvl(char **envp)
{
	int		i;
	int		j;
	char	*newshlvl;
	char	*freeme;
	char	*buf;

	i = -1;
	j = 0;
	while (envp[++i] != NULL)
	{
		if (strncmp("SHLVL=", envp[i], 6) == 0)
			break ;
	}
	if (envp[i] == NULL)
		get_bash()->env = ft_export_variable("SHLVL=1", envp);
	else
	{
		freeme = envp[i];
		while (j++ < 6)
			envp[i]++;
		buf = ft_itoa(ft_atoi(envp[i]) + 1);
		newshlvl = ft_strjoin("SHLVL=", buf);
		envp[i] = newshlvl;
		return (free(freeme), free(buf));
	}
}

char	*get_command_pointer(char *command, char **envp)
{
	char	*pwd;
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", envp[i], 4) == 0)
		{
			pwd = envp[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pwd++;
		i++;
	}
	command++;
	path = ft_strjoin(pwd, command);
	return (path);
}

char	*ft_execute_local(char *command, char **envp)
{
	char	*path;

	path = get_command_pointer(command, envp);
	return (path);
}

void	ft_wait_for_all(int pid, t_cmd_list *cmd_list)
{
	int	status;
	int	i;
	int	sig;

	i = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_exit_codes()->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			get_exit_codes()->last_exit_code = 130;
		else if (sig == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit: 3\n", 8);
			get_exit_codes()->last_exit_code = 131;
		}
	}
	while (i < cmd_list->size - 1)
	{
		wait(NULL);
		i++;
	}
}
