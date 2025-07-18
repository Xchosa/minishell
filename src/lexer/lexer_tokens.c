/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:27:12 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/14 11:10:19 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_correct_export_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == false)
		return (false);
	while (str[i])
		i++;
	return (true);
}

bool	check_syntax(t_token *token)
{
	if (token->next)
	{
		token = token->next;
		if (token->token_type == Redirect_input)
			return (false);
		if (token->token_type == Redirect_output)
			return (false);
		if (token->token_type == Append)
			return (false);
		if (token->token_type == here_doc)
			return (false);
		if (token->token_type == PIPE)
			return (false);
		return (true);
	}
	return (false);
}

bool	check_for_cmd(t_token *token)
{
	if (token->token_type == Redirect_input)
		return (true);
	else if (token->token_type == Redirect_output)
		return (true);
	else if (token->token_type == Append)
		return (true);
	else if (token->token_type == here_doc)
		return (true);
	return (false);
}

bool	lexer_token(t_token *token_lst)
{
	t_token	*cur_token;

	cur_token = token_lst;
	while (cur_token)
	{
		if (cur_token->token_type == Export_var)
		{
			if (check_correct_export_var(cur_token->token) == false)
			{
				get_exit_codes()->last_exit_code = invalid_identifier;
				return (false);
			}
		}
		if (check_for_cmd(cur_token) == true)
		{
			if (check_syntax(cur_token) == false)
			{
				get_exit_codes()->last_exit_code = syntax_error_token;
				return (false);
			}
		}
		cur_token = cur_token->next;
	}
	return (true);
}

