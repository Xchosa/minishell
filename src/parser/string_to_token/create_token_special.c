/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_special.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:58:14 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/21 14:18:45 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*create_first_token(char **line)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return (d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return (s_quote_case(line));
	else
		return (create_token(line));
}

t_token	*create_token_with_quote_case(char **line, t_token *token)
{
	(void)token;
	// skip_double_quotes(line);
	if (ft_strncmp("\"", *line, 1) == 0)
		return (d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return (s_quote_case(line));
	if (token->head->token_type == EXPORT)
	 	return (create_token_equal_as_div(line));
	else
		return (create_token(line));
}

char *swap_exit_code_in_line(char *new_line, char *tmp_line, char **line)
{
	char *exit_code;
	char *start_exit_code;

	(*line) +=2;
	exit_code = (ft_itoa(get_exit_codes()->last_exit_code));
	start_exit_code = exit_code;
	while((*exit_code) != '\0')
	{
		tmp_line = ft_charjoin(new_line, (*exit_code));
		if (!tmp_line)
			return (NULL);
		new_line = tmp_line;
		exit_code++;
	}
	free(start_exit_code);
	return (new_line);
}
