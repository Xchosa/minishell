/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/22 16:14:16 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


void skip_whitespace(char **line)
{
	while(*line)
	{
		if(ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break;
		(*line)++;
	}
}

bool	check_for_divider(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	// if (ft_strncmp (" ", &c, 1) == 0)
	// 	return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	return (false);
}


bool	(find_divider_until_whitespace_or_eof(char c)) // true
{
	if (c == '\0') // if end of line true 
		return (false);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != false) // if space true
		return (false);
	if (check_for_divider(c) == true)// if | true return true
		return (true);
	return (false);
}

bool	char_is_alpha_nbr_and_no_whitespace(char c)
{
	if (ft_isalnum(c) == true)
		return (true);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != NULL)
		return (true);
	return (false);
}

char	*update_line(char *line)
{
	int	i;

	i = 0;
	while (*line && check_for_divider(*line) == true && *line != ' ') 
        line++;
	while (*line && ft_isalnum(*line))
        line++;
	return	(&line[i]);
}
