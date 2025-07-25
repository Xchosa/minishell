/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 16:45:32 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*create_token_equal_as_div(char **content)
{
	t_token	*new_token;

	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (is_redirect(*content) == true)
	{
		new_token->token = get_token(content);
		new_token->token_type = get_token_type(new_token->token);
	}
	else
	{
		new_token->token = get_token(content);
		if ((**content) != '\0' && ft_strchr("\"\'", **content) != NULL)
			new_token->token = append_export_var(new_token->token, content);
		new_token->token_type = Export_var;
	}
	new_token->next = NULL;
	return (new_token);
}

bool	is_redirect(char *content)
{
	if (ft_strncmp ("|", content, 1) == 0)
		return (true);
	if (ft_strncmp ("<", content, 1) == 0)
		return (true);
	if (ft_strncmp (">", content, 1) == 0)
		return (true);
	return (false);
}

char	*add_char(char **content, char *tmp_token, char *new_token, int i)
{
	while (check_for_divider_without_space((*content)[i]) == true)
	{
		tmp_token = ft_charjoin(new_token, (*content)[i]);
		new_token = tmp_token;
		if (not_single_divider((*content)[i]) == false)
			return (new_token);
		(*content)++;
	}
	return (new_token);
}

char	*append_export_var(char *token_str, char **content)
{
	char	*appended_str;
	char	*next_token_str;

	next_token_str = get_export_token_in_quotes(content);
	appended_str = ft_strjoin(token_str, next_token_str);
	free(token_str);
	free(next_token_str); //thilo did this
	return (appended_str);
}

char	*get_export_token_in_quotes(char **content)
{
	char	*new_token;
	char	*tmp_token;

	new_token = ft_strdup("");
	tmp_token = NULL;
	if (!new_token)
		return (NULL);
	if (ft_strchr("\"", **content) != NULL)
	{
		skip_single_quotes(content);
		while ((**content) != '\0' && ft_strchr("\"", **content) == NULL)
			new_token = add_single_char_to_line(new_token, tmp_token, content);
	}
	else if (ft_strchr("\'", **content) != NULL)
	{
		skip_single_quotes(content);
		while ((**content) != '\0' && ft_strchr("\'", **content) == NULL)
			new_token = add_single_char_to_line(new_token, tmp_token, content);
	}
	skip_single_quotes(content);
	return (new_token);
}
