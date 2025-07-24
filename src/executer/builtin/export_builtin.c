/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:02:00 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/24 11:00:15 by tschulle         ###   ########.fr       */
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
		if (ft_strchr(envp[j], '=') != NULL && *(ft_strchr(envp[j], '=') + 1) != '\0')
		{
			s = ft_split(envp[j], '=');
			ft_printf("declare -x %s=\"%s\"\n", s[0], ft_strchr(envp[j], '=') + 1);
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

bool	ft_check_valid_identifier(char *var)
{
	char	**s;
	int		i;

	i = 0;
	if (ft_isalpha(var[0]) != 1 && var[0] != '_')
	{
		ft_putendl_fd("shell: not a valid identifier", 2);
		get_exit_codes()->last_exit_code = 1;
		return (false);
	}
	s = ft_split(var, '=');
	while (s[0][i] != '\0')
	{
		if (strrchr("-+{}!@#*^.~", s[0][i]) != NULL)
		{
			ft_putendl_fd("shell: not a valid identifier", 2);
			get_exit_codes()->last_exit_code = 1;
			return (ft_free_array(s), false);
		}
		i++;
	}
	return (ft_free_array(s), true);
}

void	ft_export(t_cmd_node *cmd_node, char **envp)
{
	int		i;
	char	**env_var;
	bool	flag;

	flag = true;
	i = 1;
	if (cmd_node->cmd[1] == NULL)
		ft_export_print(envp);
	else
	{
		while (cmd_node->cmd[i] != NULL)
		{
			env_var = ft_split(cmd_node->cmd[i], '=');
			//malloc check
			if (ft_check_valid_identifier(cmd_node->cmd[i]) == true && there_is_env_var(envp, env_var[0]) == true)
			{
				envp = ft_unset_var_by_name(envp, env_var[0]);
				envp = ft_export_variable(cmd_node->cmd[i], envp);
			}
			else if (ft_check_valid_identifier(cmd_node->cmd[i]) == true) // exit code and mssg here or in function
				envp = ft_export_variable(cmd_node->cmd[i], envp);
			else
				flag = false;
			ft_free_array(env_var);
			i++;
		}
	}
	get_bash()->env = envp;
	if (flag == false)
		get_exit_codes()->last_exit_code = 1;
	else
		get_exit_codes()->last_exit_code = 0;
}
