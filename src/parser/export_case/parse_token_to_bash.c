/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_to_bash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:39 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:07:42 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// char **extend_env_with_str(char** src, char *token)
// {
//     int i;
// 	int rows;
// 	char **cpy_env;

// 	rows = 0;
// 	while(src[rows] != NULL)
// 		rows++;
// 	cpy_env = (char **)malloc(sizeof(char*) * (rows + 2));
// 	i = 0;
//     while(i < rows || src[i])
// 	{
// 		cpy_env[i] = ft_strdup(src[i]);
// 		i++;
// 	}
//     cpy_env[i] = ft_strdup(token);
// 	cpy_env[i+1]= NULL;
// 	return(cpy_env);
// }
