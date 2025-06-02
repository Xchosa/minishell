/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:37:48 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 16:40:56 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_token	*d_quote_case(char **line)
{
	int i;
	char *tmp_token;
	t_token *new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
	return (NULL);
	new_token->token =ft_strdup("");
	i++;// soll hoch iterieren aber nicht line veraendern
	while((*line)[i] != '"')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
		free(new_token->token);
        new_token->token = tmp_token;
		i++;
	}
	new_token->token_type = TEXT;
	if((ft_strncmp("$", new_token->token, 1) == 0))
		new_token->token_type = CALL_SAVED_VAR;
	if((ft_strncmp("$?", new_token->token, 2) == 0))
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
	// (line)++;
	return (new_token);
}


t_token *create_first_token(char **line)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return(d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return(s_quote_case(line));
	if ((ft_strncmp("$?", *line, 2) == 0))
		return(call_exit_token(line));
	if ((ft_strncmp("$", *line, 1) == 0))
		return(call_saved_export_var(line));
	if ((ft_strncmp("=", *line, 1) == 0))
		return(equal_case(line));
	else
		return(create_token(*line));
}


t_token *create_token_with_quote_case(char **line, t_token *token)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return(d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return(s_quote_case(line));
	if ((ft_strncmp("$?", *line, 2) == 0))
		return(call_exit_token(line));
	if ((ft_strncmp("$", *line, 1) == 0))
		return(call_saved_export_var(line));
	// if ((ft_strncmp("=", *line, 1) == 0))
	// 	return(equal_case(line));
	if (token->head->token_type == EXPORT)
		return(create_token_equal_as_div(*line));
	else
		return(create_token(*line));
}
