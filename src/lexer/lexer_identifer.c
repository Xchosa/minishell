/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:25:55 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/02 17:27:01 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	d_quote_case_no_div(char *line)
{
	int	i;

	i = 1;
	while (ft_strncmp("\"", line, 1) != 0)
	{
		if (line[i])
			return (false);
		if (check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
	i++;
	while (line[i])
	{
		skip_whitespace(&line);
		if (check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
	return (true);
}
