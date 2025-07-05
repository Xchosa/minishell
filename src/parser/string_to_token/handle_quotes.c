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


void skip_quotes(char **line)
{
	int i;

	i = 0;
	if(((*line)[i] == '\"') && (((*line)[i +1 ] == '\"') || (*line)[i +1 ] == '\''))
	{
		while(*line)
		{
			if(ft_strchr("\"\'" , **line) != NULL)
				(*line)++;
			else 
				break;
		}
		return;
	}
	if(((*line)[i] == '\'') && (((*line)[i +1 ] == '\"') || (*line)[i +1 ] == '\''))
	{
		while(*line)
		{
			if(ft_strchr("\"\'" , **line) == NULL)
				(*line)++;
			else 
				break;
		}
		return;
	}
}


t_token	*d_quote_case(char **line)
{
	int i;
	char	*tmp_token;
	t_token *new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("");
	skip_quotes(line);
	while((*line)[i] != '"' && (*line)[i] != '\'')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
		free(new_token->token);
        new_token->token = tmp_token;
		i++;
	}
	new_token->token_type = TEXT;
	if((ft_strncmp("$", new_token->token, 1) == 0))
		new_token->token_type = CALL_SAVED_VAR;
	if((ft_strcmp("$?", new_token->token) == true))
		new_token->token_type = CALL_EXIT;
	return (new_token);
}

t_token	*s_quote_case(char **line)
{
	int i;
	char *tmp_token;
	t_token *new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("");
	i++;
	while((*line)[i] != '\'')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
		free(new_token->token);
        new_token->token = tmp_token;
		i++;
	}
	new_token->token_type = TEXT;
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
	(void)line;
	return (new_token);
}
