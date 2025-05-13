/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:02:00 by tschulle          #+#    #+#             */
/*   Updated: 2025/05/13 09:02:09 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_index(int i, char **envp)
{
	int	j;
	int	k;
	int l;
	int max;

	l = 0;
	j = 0;
	k = 0;
	max = 0;
	while (envp[max] != NULL) // ggf zum kueryen max uebergeben, sollte reichen
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
	int	i;
	int j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = ft_get_index(i, envp);
		ft_printf("declare -x %s=\"%s\"\n",ft_split(envp[j], '=')[0], ft_split(envp[j], '=')[1]);
		i++;
	}//diff: null, multiple =, oldpwd, _a.out;, kleinschreibung vor gross
}

void	ft_export_variable(char *cmd_var, char **envp)
{
	int	max;
	int	i;
	char	**newenvp;
	char	*newvar;

	max = 0;
	i = 0;
	while(envp[max] != NULL)
		max++;
	newenvp = (char **)malloc((max + 2) * sizeof(char *));
	if (newenvp == NULL)
		return;
	newvar = strdup(cmd_var);
	while (envp[i] != NULL)
	{
		newenvp[i] = strdup(envp[i]);
		i++;
	}
	newenvp[i] = newvar;
	newenvp[i + 1] = NULL;
	//free envp
	get_bash()->env = newenvp;
	ft_export_print(get_bash()->env);
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
		//	ft_check_export(cmd_node);
			ft_export_variable(cmd_node->cmd[i], envp);
			i++;
		}
	}
}
