/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:37:48 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/21 13:42:53 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*d_quote_case(char **line)
{
	t_token		*new_token;
	int			nbr_of_chars_tokenised;

	nbr_of_chars_tokenised = 0;
	skip_quotes(line);
	if (*line == NULL)
		return (NULL);
	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup("");
	if (!validate_token_str(&new_token))
		return (new_token = NULL);
	nbr_of_chars_tokenised = process_content_to_token(line, new_token);
	if (nbr_of_chars_tokenised == -1)
	{
		free_single_token(&new_token);
		return (NULL);
	}
	define_token_type(new_token);
	new_token->next = NULL;
	return (new_token);
}

void	define_token_type(t_token *new_token)
{
	new_token->token_type = TEXT;
	if ((ft_strncmp("$", new_token->token, 1) == 0))
		new_token->token_type = CALL_SAVED_VAR;
	if ((ft_strcmp("$?", new_token->token) == true))
		new_token->token_type = CALL_EXIT;
}

t_token	*s_quote_case(char **line)
{
	t_token	*new_token;

	skip_quotes(line);
	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup("");
	if (!validate_token_str(&new_token))
		return (NULL);
	if (process_s_q_content_to_token(line, new_token) == false)
	{
		free_single_token(&new_token);
		return (NULL);
	}
	new_token->token_type = TEXT;
	return (new_token);
}

t_token	*equal_case(char **line)
{
	t_token	*new_token;

	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup("=");
	new_token->token_type = Export_var;
	line++;
	return (new_token);
}
