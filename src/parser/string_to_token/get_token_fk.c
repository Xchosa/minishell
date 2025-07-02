/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_fk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:52:50 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/02 18:00:08 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*tokenise_divider(char *content, char *new_token)
{
	char *tmp_token;

	int i;
	i = 0;
	while (check_for_divider_without_space(content[i]) == true)
	{
		tmp_token = ft_charjoin(new_token, content[i]);
		free(new_token);
		new_token = tmp_token;
		if(not_single_divider(content[i])== false )
			return (new_token);
		i++;
	}
	return (new_token);
}

char* get_token(char *content)
{
	int		i;
	char	*new_token;
	char	*tmp_token;

	i = 0;
	new_token = ft_strdup("");
	while (content[i] != '\0' && check_for_divider_with_space(content[i]) == false)
	{
		if (char_is_alpha_nbr_and_no_whitespace(content[i]))
		{
			tmp_token = ft_charjoin(new_token, content[i]);
			free(new_token);
            new_token = tmp_token;
		}
		if (check_for_divider_with_space(content[i +1 ]) == true)
			return (new_token);
		i++;
	}
	if (check_for_divider_without_space(content[i]) == true)
	{
		new_token = tokenise_divider(content + i, new_token);
	}
	return (new_token);
}

t_type	append_or_redirect_output(char *content)
{
	int i;
	
	i = 0;
	if (content[i+1] == '>')
		return (Append);
	else
		return(Redirect_output);
}

t_type get_token_type(char *content)
{
	int i;

	i = 0;
	if(content[i] == '|')
		return(PIPE);
	if (content[i] == '>')
		return(append_or_redirect_output(&content[i]));
	if (content[i] == '<')
	{
		if (content[i+1] == '<')
			return (here_doc);
		else
			return (Redirect_input);
	}
	if(ft_strcmp( "export", content) == true)
		return (EXPORT);
	if(ft_strcmp(content, "~") == true)
		return(Tilde);
	if (ft_strchr(content, '$') != NULL)
		return (Mix_Export_var);
	return(TEXT);
}


// compares the hole string not just a specific len
bool	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	if((s1[i] == '\0') && (s2[i] == '\0'))
		return (true);

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return((s1[i] == '\0') && (s2[i] == '\0'));
}
