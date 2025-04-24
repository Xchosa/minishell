/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:57:07 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 16:27:06 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

char	*update_line_unitl_d_quotes(char *line)
{
	line++;
	while(ft_strncmp( "\"", line, 1) != 0)
 		line++;
	line++;
	return (line);
}

char	*update_line_unitl_s_quotes(char *line)
{
	line++;
	while(ft_strncmp( "\'", line, 1) != 0)
		line++;
	line++;
	return (line);
}


char	*update_line(char *line)
{
	int	i;
	bool flag;

	i = 0;
	flag = false;
	skip_whitespace(&line);
	if (ft_strncmp( "\"", line, 1) == 0)
		return(update_line_unitl_d_quotes(line));
	if (ft_strncmp( "\'", line, 1) == 0)
		return(update_line_unitl_s_quotes(line));
	while (*line && check_for_divider_with_space(*line) == true)
	{
		line++;
		flag = true;
	}
	if( flag == false)
	{
		while (*line && ft_isalnum(*line))
			line++;
	}
	return	(line);
}