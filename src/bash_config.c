/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:57:23 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 15:02:39 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_bash	*get_bash(void)
{
	static t_bash	bash;

	return (&bash);
}

bool	init_bash(char **env, int argc)
{
	t_bash	*bash;

	bash = get_bash();
	if (argc == 1)
	{
		bash->env = cpychar_arr(env);
		if (!bash->env)
			return (false);
	}
	ft_increase_shlvl(bash->env);
	return (true);
}

void	clean_bash_env(void)
{
	t_bash	*bash;

	bash = get_bash();
	if (bash->env)
	{
		ft_free_array(bash->env);
	}
	bash->env = NULL;
}

// cpy envp in bash_envp
//  rows counts until 1 only 
// see copilot
char	**cpychar_arr(char **src)
{
	int		i;
	int		rows;
	char	**cpy_env;

	rows = 0;
	while (src[rows] != NULL)
		rows++;
	cpy_env = (char **)malloc(sizeof(char*) * (rows + 1));
	i = 0;
	while (i < rows || src[i])
	{
		cpy_env[i] = ft_strdup(src[i]);
		i++;
	}
	cpy_env[i]= NULL;
	return (cpy_env);
}

void	ft_print_array(char **src)
{
	int i;

	i = 0;
	while (src[i])
	{
		printf("%s\n", src[i]);
		i++;
	}
}
