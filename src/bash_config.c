/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:57:23 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/05 15:48:02 by poverbec         ###   ########.fr       */
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
	t_bash *bash;
	
	bash = get_bash();
	if (argc == 1)
	{
		bash->env = cpychar_arr(env);
		if(!bash->env)
			return(false);
	//config->token_lst = NULL;
	}
	return (true);
	
}

// cpy envp in bash_envp
//  rows counts until 1 only 
// see copilot
char **cpychar_arr(char** src)
{
    int i;
	int rows;
	char **cpy_env;

	char *t3 = src[0];
	char *y4 = src[1];
	char *t4 = src[2];
	char *i5 = src[4];
	
	printf("%s\n", t3);
	printf("%s\n", y4);
	printf("%s\n", t4);
	printf("%s\n", i5);

	rows = 0;
	while(src[rows] != NULL)
		rows++;
	cpy_env = (char **)malloc(sizeof(char*) * (rows + 1));
	i = 0;
    while(i < rows || src[i])
	{
		cpy_env[i] = ft_strdup(src[i]);
		i++;
	}
	cpy_env[i]= NULL;
	return(cpy_env);
}


void ft_print_array(char **src)
{
	int i;

	i = 0;
	
	while(src[i])
	{
		printf("%s\n", src[i]);
		i++;
	}
}