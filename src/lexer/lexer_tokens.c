/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:27:12 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 10:22:29 by poverbec         ###   ########.fr       */
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
		if (check_syntax_heredoc(token->token) == false)
			return (false);
		if (token->token_type == PIPE)
			return (false);
		return (true);
	}
	return (false);
}

bool	lexer_token(t_token *token_lst, char *original_line)
{
	t_token	*cur_token;

	(void)original_line;
	if (check_last_node_syntax(token_lst) == false)
		return (false);
	cur_token = token_lst;
	while (cur_token)
	{
		if (check_for_cmd(cur_token) == true)
		{
			if (check_syntax(cur_token) == false)
			{
				get_exit_codes()->last_exit_code = SYNTAX_ERROR_TOKEN;
				return (false);
			}
		}
		cur_token = cur_token->next;
	}
	return (true);
}

bool	check_last_node_syntax(t_token *token_lst)
{
	t_token	*last_token;
	int		token_type;

	last_token = tokenlast(token_lst);
	if (last_token == NULL)
		return (true);
	token_type = last_token->token_type;
	if (token_type == Redirect_input || token_type == Redirect_output
		|| token_type == Append || token_type == PIPE)
		return (false);
	return (true);
}
