/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:02:00 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/07 18:02:51 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_get_index(int i, char **envp)
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
	while (j != max - i && l < max)
	{
		j = 0;
		while (envp[k] != NULL)
		{
			if (ft_strncmp(envp[l], envp[k], 200) < 0)
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
	char	*s;

	i = 0;
	s = ft_split(envp[j], '=');
	while (envp[i] != NULL)
	{
		j = ft_get_index(i, envp);
		ft_printf("declare -x %s=\"%s\"\n", s[0], s[1]);
		i++;
	}//diff: null, multiple =, oldpwd, _a.out;, kleinschreibung vor gross
	free(s);
	get_exit_codes()->last_exit_code = 0;
}

void	ft_export_variable(char *cmd_var, char **envp)
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
		return ;
	newvar = ft_strdup(cmd_var);
	while (envp[i] != NULL)
	{
		newenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	newenvp[i] = newvar;
	newenvp[i + 1] = NULL;
	ft_free_array(envp);
	get_bash()->env = newenvp;
	//ft_export_print(get_bash()->env);
	get_exit_codes()->last_exit_code = 0;
}

bool	ft_check_valid_identifier(char *var) // check for overwrite?
{
	if (ft_isalpha(var[0]) != 1 && var[0] != '_')
	{
		get_exit_codes()->last_exit_code = 1;
		return (false);
	}
	return (true);
}

void	ft_export(t_cmd_node *cmd_node, char **envp)
{
	int	i;

	i = 1;
	if (cmd_node->cmd[1] == NULL)
		ft_export_print(envp);
	else
	{
		while (cmd_node->cmd[i] != NULL)
		{
			if (ft_check_valid_identifier(cmd_node->cmd[i]) == false) //doesnt do shit yet i believe because tokeniser does it, but not cerrect always
				return ;
			ft_export_variable(cmd_node->cmd[i], envp);
			i++;
		}
	}
}
