/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:08:09 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/15 16:34:52 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*call_exit_token(char **line)
{
	t_token	*new_token;

	(*line)++;
	(*line)++;
	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup("$?");
	new_token->token_type = CALL_EXIT;
	new_token->next = NULL;
	return (new_token);
}

// t_token	*call_saved_export_var(char **line)
// {
// 	char		*tmp_token;
// 	char		*new_token_str;
// 	t_token		*new_token;

// 	new_token = malloc (sizeof(t_token));
// 	if (!new_token)
// 		return (NULL);
// 	new_token_str = ft_strdup("");
// 	if (!validate_token_str(&new_token))
// 		return (NULL);
// 	while (**line && (**line) != ' ' && **line != '>'
// 		&& **line != '<' && **line != '|')
// 	{
// 		tmp_token = ft_charjoin(new_token_str, (**line));
// 		new_token_str = tmp_token;
// 		(*line)++;
// 		if (ft_strchr("\"\'", (**line)) != NULL)
// 			break ;
// 	}
// 	new_token->token = new_token_str;
// 	new_token->token_type = CALL_SAVED_VAR;
// 	new_token->next = NULL;
// 	return (new_token);
// }

t_token	*call_saved_export_var(char **line)
{
	char		*tmp_token;
	char		*new_token_str;
	t_token		*new_token;

	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token_str = ft_strdup("");
	if (!validate_token_str(&new_token))
		return (NULL);
	while (**line && (**line) != ' ' && **line != '>'
		&& **line != '<' && **line != '|')
	{
		tmp_token = ft_charjoin(new_token_str, (**line));
		new_token_str = tmp_token;
		(*line)++;
		if (ft_strchr("\"", (**line)) != NULL)
			break ;
	}
	new_token->token = new_token_str;
	new_token->token_type = CALL_SAVED_VAR;
	new_token->next = NULL;
	return (new_token);
}
