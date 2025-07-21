/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_line_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:22:06 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/21 15:58:15 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


char *add_single_char_to_line(char *new_line, char *tmp_line, char **line)
{
	if (**line != '\0')
	{
		tmp_line= ft_charjoin(new_line, (**line));
		if (!tmp_line)
			return (NULL);
		new_line = tmp_line;
		(*line)++;
		return (new_line);
	}
	return (new_line);
}

char *get_env_in_line( char **line)
{
	char *tmp_line;
	char *env_str;
	char *return_str;

	env_str = ft_strdup("");
	if(!(*line))
		return(env_str);
	while(**line != '\0' && ft_strchr("$<>|\"\' ", (**line)) == NULL)
	{
		tmp_line = ft_charjoin(env_str, (**line));
        if (!tmp_line)
        	return (env_str = ft_strdup(""));
        env_str = tmp_line;
		(*line)++;
	}
	if(!(*env_str))
		return(env_str);
	return_str = get_var_from_env(get_bash()->env, env_str);
	return(return_str);
}
