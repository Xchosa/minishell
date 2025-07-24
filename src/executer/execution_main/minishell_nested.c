/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_nested.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:59:07 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/24 18:54:51 by tschulle         ###   ########.fr       */
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

	i = - 1;
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
		pwd++; //can break if PWD unset. important? 
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
	if (access(path, X_OK) == 0)
		return (path);
	else
		return (free (path), NULL);
}
