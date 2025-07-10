/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:48:02 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 13:48:31 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_lexer_token_and_free(t_token *token, char *line)
{
	if (lexer_token(token) == false)
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
	if (line == NULL)
		return (false);
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		print_lexer_error_message(line);
		return (false);
	}
	return (true);
}
