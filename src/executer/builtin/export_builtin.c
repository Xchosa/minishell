/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:02:00 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/25 15:25:44 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_get_index(int pos_to_print, char **envp)
{
	int	j;
	int	k;
	int	l;
	int	max;

	l = 0;
	j = 0;
	k = 0;
	max = 0;
	while (envp[max] != NULL)
		max++;
	while (j != max - pos_to_print && l < max)
	{
		j = 0;
		while (envp[k] != NULL)
		{
			if (ft_strncmp(envp[l], envp[k], 1024) <= 0)
				j++;
			k++;
		}
		k = 0;
		l++;
	}
	return (l - 1);
}

void	ft_export_print(char **envp)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	while (envp[i] != NULL)
	{
		j = ft_get_index(i, envp);
		if (ft_strchr(envp[j], '=') != NULL
			&& *(ft_strchr(envp[j], '=') + 1) != '\0')
		{
			s = ft_split(envp[j], '=');
			ft_printf("declare -x %s=\"%s\"\n", s[0],
				ft_strchr(envp[j], '=') + 1);
			ft_free_array(s);
		}
		else
			ft_printf("declare -x %s\n", envp[j]);
		i++;
	}
	get_exit_codes()->last_exit_code = 0;
}

char	**ft_export_variable(char *cmd_var, char **envp)
{
	int		max;
	int		i;
	char	**newenvp;
	char	*newvar;

	max = 0;
	i = 0;
	while (envp[max] != NULL)
		max++;
	newenvp = (char **)malloc((max + 2) * sizeof(char *));
	if (newenvp == NULL)
		return (NULL);
	newvar = ft_strdup(cmd_var);
	if (newvar == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		newenvp[i] = envp[i];
		i++;
	}
	newenvp[i] = newvar;
	newenvp[i + 1] = NULL;
	free(envp);
	return (newenvp);
}

char	**ft_export_var_valid(char **envp, char *var)
{
	char	**env_var;

	env_var = ft_split(var, '=');
	if (there_is_env_var(envp, env_var[0]) == true)
	{
		envp = ft_unset_var_by_name(envp, env_var[0]);
		envp = ft_export_variable(var, envp);
	}
	else
		envp = ft_export_variable(var, envp);
	ft_free_array(env_var);
	return (envp);
}

void	ft_export(t_cmd_node *cmd_node, char **envp)
{
	int		i;

	i = 1;
	get_exit_codes()->last_exit_code = 0;
	if (cmd_node->cmd[1] == NULL)
		ft_export_print(envp);
	else
	{
		while (cmd_node->cmd[i] != NULL)
		{
			if (ft_check_valid_identifier(cmd_node->cmd[i]) == true)
				envp = ft_export_var_valid(envp, cmd_node->cmd[i]);
			i++;
		}
	}
	get_bash()->env = envp;
}
