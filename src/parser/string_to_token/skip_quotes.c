/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:35:25 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 11:36:05 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_quotes(char **line)
{
	// int	i;

	// i = 0;
	// if (skip_whitespace_and_check_for_eof(line) == false)
	// 	return ;
	// if (skip_d_quotes_and_following_quotes(line, i) == true)
	// 	return ;
	// if (skip_s_quotes_and_following_qutes(line, i) == true)
	// 	return ;
	skip_single_quotes(line);
	// if((*line))
	// 	(*line)++;
}

bool	skip_d_quotes_and_following_quotes(char **line, int i)
{
	if (((*line)[i] == '\"') && (((*line)[i + 1] == '\"')
		|| (*line)[i + 1] == '\''))
	{
		while (*line && **line != '\0')
		{
			if (ft_strchr("\"\'", **line) != NULL)
				(*line)++;
			else
				break ;
		}
		return (true);
	}
	return (false);
}

bool	skip_s_quotes_and_following_qutes(char **line, int i)
{
	if (((*line)[i] == '\'') && (((*line)[i + 1] == '\"')
			|| (*line)[i + 1] == '\''))
	{
		while (*line && **line != '\0')
		{
			if (ft_strchr("\"\'",**line) != NULL)
				(*line)++;
			else
				break ;
		}
		return (true);
	}
	return (false);
}

void	skip_single_quotes(char **line)
{
	int	i;

	i = 0;
	if(!(*line))
		return ;
	else if (((*line)[i] == '\'') && ((*line)[i +1 ] == '\0'))
	{
		(*line)++;
		return ;
	}
	else if (((*line)[i] == '\"') && ((*line)[i +1 ] == '\0'))
	{
		(*line)++;
		return ;
	}
	else if (ft_strchr("\"\'",**line) != NULL)
		(*line)++;
}
