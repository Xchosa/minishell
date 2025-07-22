/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:27:12 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/22 16:31:39 by poverbec         ###   ########.fr       */
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
	//if(token->next 
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
bool	check_syntax_heredoc(char *heredoc_del)
{
	int i;

	i = 0;
	while(heredoc_del[i])
	{
		if(ft_strchr(".!?-@#$^&*(){}", heredoc_del[i]) != NULL)
			return (false);
		i++;
	}
	return (true);
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
				get_exit_codes()->last_exit_code = syntax_error_token;
				// token_lst = cur_token->head;
				// print_error_message(&token_lst, original_line);
				return (false);
			}
		}
		cur_token = cur_token->next;
	}
	// token_lst = cur_token->head;
	return (true);
}

bool	check_last_node_syntax(t_token *token_lst)
{
	t_token *last_token;
	int		token_type;
	
	last_token = tokenlast(token_lst);
	token_type = last_token->token_type;
	if (token_type == Redirect_input || token_type == Redirect_output
		|| token_type == Append || token_type == PIPE )
			return (false);
	return (true);
}


bool	lexer_correct_export_var(t_token *token_lst, char *original_line)
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
				print_error_message(&token_lst, original_line);
				return (false);
			}
		}
		cur_token = cur_token->next;
	}
	return (true);
}

bool	final_lexer(t_token *token_lst, char *original_line)
{
	if (lexer_token(token_lst, original_line) == false)
	{
		print_error_message(&token_lst, original_line);
		return (false);
	}
	if (tokeniser_successful(token_lst, original_line) == false)
	{
		print_error_message(&token_lst, original_line);
		return (false);
	}
	// if (lexer_correct_export_var(token_lst, original_line) == false)
	// 	return (false);
	return (true);
}
