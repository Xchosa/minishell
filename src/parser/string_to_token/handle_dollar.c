/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:08:09 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 11:48:24 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*call_exit_token(char **line)
{
	t_token *new_token;

	(*line)++;
	(*line)++;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("$?");
	new_token->token_type = CALL_EXIT;
	return (new_token);
}


t_token	*call_saved_export_var(char **line)
{
	int			i;
	char		*tmp_token;
	t_token	*new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup("");
	if (!validate_token_str(&new_token))
		return (NULL);
	while ((*line)[i] != ' ' && (*line)[i] != '\0')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
        new_token->token = tmp_token;
		i++;
		if (ft_strchr("\"" , (*line)[i]) != NULL) // every token with \' after $xx nicht aufloesen
			break ;
	}
	*line += i;
	new_token->token_type = CALL_SAVED_VAR;
	return (new_token);
}
