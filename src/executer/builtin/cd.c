/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:41:44 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/24 11:45:26 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*get_old_pwd(char **envp)
{
	int		i;
	char	*oldpwd;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("OLDPWD=", envp[i], 7) == 0)
			break ;
		i++;
	}
	oldpwd = envp[i];
	i = 0;
	if (oldpwd == NULL)
		return (NULL);
	while (i < 7)
	{
		oldpwd++;
		i++;
	}
	return (oldpwd);
}

void	ft_cd(t_cmd_node *cmd_node, char **envp)
{
	char	*s;
	if (cmd_node->cmd[1] == NULL)
	{
		chdir(get_home_path(envp));
		ft_update_env_cd(cmd_node, envp);
		get_exit_codes()->last_exit_code = 0;
		return ;
	}
	if (strncmp(cmd_node->cmd[1], "-", 2) == 0)
	{
		if (there_is_env_var(envp, "OLDPWD") == false)
		{
			ft_putendl_fd("shell: cd : OLDPWD not set", 2);
			get_exit_codes()->last_exit_code = 1;
			return ;
		}
		free(cmd_node->cmd[1]);
		s  = ft_strdup(get_old_pwd(envp));
		cmd_node->cmd[1] = s;//segfault hier aber liegt glaube ich an ft_strlen oder strdup nullchecks
		printf("%s\n", cmd_node->cmd[1]);
	}
	if (chdir(cmd_node->cmd[1]) != 0)
	{
		get_exit_codes()->last_exit_code = 1;
		perror("shell");
		return ;
	}
	ft_update_env_cd(cmd_node, envp);
	get_exit_codes()->last_exit_code = 0;
}
