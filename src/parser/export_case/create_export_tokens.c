/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 11:41:19 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static bool	check_for_div_export(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("\"", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("\'", &c, 1) == 0)
		return (true);
	return (false);
}
	// if (ft_strncmp ("=", &c, 1) == 0)
	// 	return (true);

bool	find_error_chars(char *line)
{
	while (line)
	{
		if (ft_strchr("\t\n\v\f\r+-!@#$^&*;()_={}", (*line)) == NULL)
			return (false);
		line++;
	}
	return true;
}

t_token	*create_token_equal_as_div(char **content)
{
	t_token	*new_token;

	if (find_error_chars(*content) == false)
		return (NULL);
	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = get_token_equal_as_div(content);
	new_token->token_type = Export_var;
	// if no equal -> get_type 
	new_token->next = NULL;
	return (new_token);
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

char	*get_token_equal_as_div(char **content)
{
	int		i;
	char	*new_token;
	char	*tmp_token;

	i = 0;
	new_token = ft_strdup("");
	if (!new_token)
		return (NULL);
	while ((*content)[i] != '\0'
		&& check_for_div_export((*content)[i]) == false)
	{
		if (char_is_alpha_nbr_and_no_whitespace((*content)[i]))
		{
			tmp_token = ft_charjoin(new_token, (*content)[i]);
			free(new_token);
			new_token = tmp_token;
		}
		if (check_for_div_export((*content)[i +1]) == true)
		{
			*content += i + 1;
			return (new_token);
		}
		(*content)++;
	}
	while (check_for_divider_without_space((*content)[i]) == true)
		new_token = add_char(content, tmp_token, new_token, i);
	return (new_token);
}




