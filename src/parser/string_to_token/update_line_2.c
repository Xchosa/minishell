/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:13:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 14:23:48 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_for_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

char	*handle_regular_token(char *line)
{
	while (*line && (ft_isalnum(*line) || special_char_no_divider(*line)))
	{
		line++;
	}
	return (line);
}
