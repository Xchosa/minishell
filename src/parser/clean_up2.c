/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:48:02 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/22 15:59:20 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_lexer_token_and_free(t_token *token, char *line)
{
	if (lexer_token(token, line) == false)
	{
		print_error_message(&token, line);
		free(line);
		free(token);
		return (false);
	}
	return (true);
}

bool	check_lexer_and_free(char *line)
{
	char	*original_line;

	original_line = line;
	if (line == NULL)
		return (false);
	skip_whitespace(&line);
	if (*line == '\0')
	{
		free(original_line);
		return (false);
	}
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_error_token;
		print_lexer_error_message(line);
		return (false);
	}
	return (true);
}
