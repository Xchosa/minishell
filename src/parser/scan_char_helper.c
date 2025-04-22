/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/22 09:52:57 by poverbec         ###   ########.fr       */
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
		return (false);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (false);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (false);
	if (ft_strncmp (">", &c, 1) == 0)
		return (false);
	if (ft_strncmp (";", &c, 1) == 0)
		return (false);
	return (true);
}

char	*update_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (check_for_divider(line[i])== false)
			break;
		i++;
	}
	return	(&line[i]);
}