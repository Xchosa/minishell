/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:11 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 14:10:12 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void clean_token_lst_and_line(t_token *token_lst, char *line)
{
	if(!token_lst)
		clean_token_lst(token_lst);
	if(!line)
		free(line);
}

void clean_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	if(!token_lst)
		return;
	while(token_lst)
	{
		tmp = token_lst->next;
		if(token_lst->next)
		{
			free(token_lst->token);
		}
		free(token_lst);
		token_lst = tmp;
	}
}

void free_single_token(t_token **token)
{
	if (*token)
	{
		free((*token)->token);
		free(*token);
		*token = NULL;
	}
}

bool	tokeniser_successful(t_token *token_lst, char *line)
{
	if (!token_lst)
	{
		free(line);
		return (false);
	}
	return (true);
}

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
		free(line);
		return (false);
	}
	return (true);
}
