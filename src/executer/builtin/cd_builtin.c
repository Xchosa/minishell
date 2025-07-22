/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:31:57 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/22 14:00:50 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	**ft_add_absolute_path(t_cmd_node *cmd_node, char **envp)
{
	int		i;
	char	*buf;
	char	*re;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			buf = envp[i];
			re = ft_strjoin("PWD=", cmd_node->cmd[1]);
			if (re == NULL)
				return (NULL);
			envp[i] = re;
			free(buf);
			if (envp[i][ft_strlen(envp[i]) - 1] == '/')
				envp[i][ft_strlen(envp[i]) - 1] = '\0';
			break ;
		}
		i++;
	}
	return (envp);
}

char	**ft_add_parent(char **envp)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			len = ft_strlen(envp[i]);
			while (envp[i][len - 1] != '/')
				len--;
			len--;
			if (len > 4)
				envp[i] = ft_substr(envp[i], 0, len);
			else
				envp[i] = ft_substr(envp[i], 0, 5);
		}
		i++;
	}
	return (envp);
}

char	**ft_add_tilde(char **envp)
{
	int		j;
	char	*newpwd;
	char	*home;
	char	*buf;

	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], "PWD=", 4) == 0)
			break ;
		j++;
	}
	buf = envp[j];
	home = get_home_path(envp);
	if (home == NULL)
		ft_putendl_fd("shell: cd: HOME not set", 2);
	else
	{
		newpwd = ft_strjoin("PWD=", home);
		if (newpwd == NULL)
			return (NULL);
		envp[j] = newpwd;
		free(buf);
	}
	return (envp);
}

char	**ft_add_relative_path(t_cmd_node *cmd_node, char **envp)
{
	char	**path_array;
	int		i;

	i = 0;
	path_array = ft_split(cmd_node->cmd[1], '/' );
	while (path_array[i] != NULL)
	{
		if (ft_strncmp("..", path_array[i], 2) == 0)
			envp = ft_add_parent(envp);
		else if (!(ft_strncmp(".", path_array[i], 1) == 0))
			envp = ft_add_pwd(path_array[i], envp);
		i++;
	}
	ft_free_array(path_array);
	return (envp);
}

void	ft_update_env_cd(t_cmd_node *cmd_node, char **envp) //bool??
{
	char	**re;

	re = NULL;
	if (there_is_env_var(envp, "OLDPWD=") == true)
		re = ft_delete_old_pwd(envp);
	if (re == NULL)
		return ;
	envp = re;
	re = ft_add_old_pwd(envp);
	if (re == NULL)
		return ;
	envp = re;
	if (cmd_node->cmd[1] == NULL)
		envp = ft_add_tilde(envp); //kann failen? bool?
	else if (ft_strncmp("/", cmd_node->cmd[1], 1) == 0)
		envp = ft_add_absolute_path(cmd_node, envp);
	else
		envp = ft_add_relative_path(cmd_node, envp);
	get_bash()->env = envp; //leaks hier? immer envp return vlaue checken
}
