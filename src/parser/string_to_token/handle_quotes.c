/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:37:48 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/03 14:30:39 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token	*d_quote_case(char **line)
{
	t_token *new_token;
	int 	nbr_of_chars_tokenised;

	nbr_of_chars_tokenised = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("");
	if (!validate_token_str(&new_token))
        return (NULL);
	skip_quotes(line);
	nbr_of_chars_tokenised = process_content_to_token(line, new_token);
	if(nbr_of_chars_tokenised == -1)
	{
		free_single_token(&new_token);
		return (NULL);
	}
	new_token->token_type = TEXT;
	if((ft_strncmp("$", new_token->token, 1) == 0))
		new_token->token_type = CALL_SAVED_VAR;
	if((ft_strcmp("$?", new_token->token) == true))
		new_token->token_type = CALL_EXIT;
	*line += nbr_of_chars_tokenised ;
	return (new_token);
}

t_token	*s_quote_case(char **line)
{
	t_token *new_token;
	int 	nbr_of_chars_tokenised;

	nbr_of_chars_tokenised = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("");
	if (!validate_token_str(&new_token))
	{
		// if (new_token)
        //     free_single_token(&new_token);
        return (NULL);
	}
	skip_quotes(line);
	nbr_of_chars_tokenised = process_content_to_token(line, new_token);
	if(nbr_of_chars_tokenised == -1)
	{
		free_single_token(&new_token);
		return (NULL);
	}
	new_token->token_type = TEXT;
	*line += nbr_of_chars_tokenised;
	return (new_token);
}

t_token	*equal_case(char **line)
{
	t_token *new_token;

	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("=");
	new_token->token_type = Export_var;
	line++;
	return (new_token);
}

