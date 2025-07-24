/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:35:42 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/24 09:57:52 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	**ft_unset_var_by_index(char **envp, int j)
{
	char	**newenvp;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (envp[size] != NULL)
		size++;
	newenvp = (char **)malloc(size * sizeof(char *));
	if (newenvp == NULL)
		return (NULL);
	while (i < size - 1)
	{
		if (i < j)
			newenvp[i] = envp[i];
		else
			newenvp[i] = envp[i + 1];
		i++;
	}
	newenvp[i] = NULL;
	free(envp);
	return (newenvp);
}

char	**ft_unset_var_by_name(char **envp, char *env_var)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(env_var);
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], env_var, len) == 0
			&& ((envp[j][len] == '=') || envp[j][len] == '\0'))
		{
			envp = ft_unset_var_by_index(envp, j);
			if (envp == NULL)
			{
				get_exit_codes()->last_exit_code = 1;
				ft_putendl_fd("malloc fail in unset\n", 2);
				return (NULL);
			}
			break ;
		}
		j++;
	}
	return (envp);
}

void	ft_unset(t_cmd_node *cmd_node, char **envp)
{
	int		i;
	bool	flag;

	flag = true;
	i = 0;
	while (cmd_node->cmd[i] != NULL)
	{
		if (ft_check_valid_identifier(cmd_node->cmd[i]) == true)
			envp = ft_unset_var_by_name(envp, cmd_node->cmd[i]);
		else
			flag = false;
		i++;
	}
	if (flag == true)
		get_exit_codes()->last_exit_code = 0;
	else
		get_exit_codes()->last_exit_code = 1;
	get_bash()->env = envp;
}
