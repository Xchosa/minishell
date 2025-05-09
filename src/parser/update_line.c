/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:57:07 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/06 11:20:19 by poverbec         ###   ########.fr       */
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


bool	pipe_or_simec(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	return (false);
}

int special_charcter_no_divider(char c)
{
	if (c == '-')
		return (1);
	if (c == '=')
		return (1);
	return (0);
}
char	*update_line_until_space(char *line)
{
	line++;
    while (*line && ft_strncmp(" ", line, 1) != 0)
    {
        line++;
    }
    return (line);
}

char	*update_line(char *line)
{
	bool flag;

	flag = false;
	skip_whitespace(&line);
	if (ft_strncmp( "\"", line, 1) == 0)
		return(update_line_unitl_d_quotes(line));
	if (ft_strncmp( "\'", line, 1) == 0)
		return(update_line_unitl_s_quotes(line));
	if ((ft_strncmp( "$'", line, 1) == 0))
		return(update_line_until_space(line));
	while (*line && check_for_divider_with_space(*line) == true)
	{
		if(pipe_or_simec(*line)== true)
		{
			line++;
			return(line);
		}
		line++;
		flag = true;
	}
	if( flag == false)
	{
		while (*line && (ft_isalnum(*line) || special_charcter_no_divider(*line)))
			line++;
	}
	return	(line);
}
