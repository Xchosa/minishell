/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:08:33 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/07 09:24:56 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_whitespace(char **line)
{
	while (*line)
	{
		if (ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break;
		(*line)++;
	}
}

bool	skip_whitespace_and_check_for_eof(char **line)
{
	bool	not_eof;
	not_eof = true;
	while (**line != '\0')
	{
		if (ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break ;
		(*line)++;
	}
	if (**line == '\0')
	{
		return (not_eof = false);
	}
	return (not_eof);
}



// bool	find_divider_until_whitespace_or_eof(char c) // true
// {
// 	if (c == '\0') // if end of line true 
// 		return (false);
// 	if (ft_strnstr("\r\n\v\t ", &c, 1) != false) // if space true
// 		return (false);
// 	if (check_for_divider_without_space(c) == true)// if | true return true
// 		return (true);
// 	return (false);
// }


bool	char_is_alpha_nbr_and_no_whitespace(char c)
{
	if (ft_isalnum(c) == true)
		return (true);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != NULL)
		return (true);
	if (ft_strchr(".,;?!*$_", c) != NULL)
		return (true);
	if (ft_strncmp ("-", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("/", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("=", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("~", &c, 1) == 0)
		return (true);
	return (false);
}

