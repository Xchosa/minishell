/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:22:15 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 11:22:23 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// fuer $USER -> 'testcase' reinschreiben
// letzter schritt erst mit env abgleichen 
char	*extend_line(char **line)
{
	char	*new_line;
	char	*tmp_line;
	char	*original_line;

	original_line = (*line);
	tmp_line = NULL;
	new_line = ft_strdup("");
	while (**line != '\0')
	{
		if (**line != '\0' && ft_strchr("\"", **line) != NULL)
		{
			new_line = add_single_char_to_line(new_line, tmp_line, line);
			while (**line != '\0' && ft_strchr("\"", **line) == NULL)
				new_line = d_qoutes_swap_dollar_var_with_env_var(new_line,
						tmp_line, line);
		}
		if (**line != '\0' && ft_strchr("\'", **line) != NULL)
			new_line = add_s_quotes_str_to_line(new_line, tmp_line, line);
		if (**line != '\0' && ft_strchr("$~", **line) != NULL)
			new_line = swap_dollar_var_with_env_var(new_line, tmp_line, line);
		else if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
	}
	free(original_line);
	return (new_line);
}

//get_env_in_line iterates line up until a $var is done 
char	*d_qoutes_swap_dollar_var_with_env_var(char *new_line,
	char *tmp_line, char **line)
{
	if (ft_strncmp("$ ", (*line), 2) == 0)
	{
		new_line = add_single_char_to_line(new_line, tmp_line, line);
		return (new_line);
	}
	else if (ft_strncmp("$?", (*line), 2) == 0)
		new_line = swap_exit_code_in_line(new_line, tmp_line, line);
	else if (ft_strchr("$", **line) != NULL)
	{
		new_line = extend_line_with_env_str(new_line, tmp_line, line);
		return (new_line);
	}
	else if (**line != '\0')
		new_line = add_single_char_to_line(new_line, tmp_line, line);
	if (ft_strchr("\"", (**line)) != NULL)
		new_line = add_single_char_to_line(new_line, tmp_line, line);
	return (new_line);
}

char	*add_s_quotes_str_to_line(char *new_line, char *tmp_line, char **line)
{
	if (**line != '\0' && ft_strchr("\'", **line) != NULL)
	{
		if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		while (**line != '\0' && ft_strchr("\'", (**line)) == NULL)
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		return (new_line);
	}
	return (new_line);
}

char	*swap_dollar_var_with_env_var(char *new_line,
	char *tmp_line, char **line)
{
	if (ft_strncmp("$ ", (*line), 2) == 0)
	{
		new_line = add_single_char_to_line(new_line, tmp_line, line);
		new_line = add_single_char_to_line(new_line, tmp_line, line);
	}
	else if (ft_strncmp("$?", (*line), 2) == 0)
		new_line = swap_exit_code_in_line(new_line, tmp_line, line);
	else if (ft_strncmp("~", (*line), 1) == 0)
		new_line = extend_line_with_tilde(new_line, tmp_line, line);
	else if (ft_strchr("$", **line) != NULL)
		new_line = extend_line_with_env_str(new_line, tmp_line, line);
	return (new_line);
}

char	*extend_line_with_env_str(char *new_line, char *tmp_line, char **line)
{
	char	*env_str;
	char	*buf;

	if (ft_strchr("$", **line) != NULL)
	{
		(*line)++;
		env_str = get_env_in_line(line);
		buf = env_str;
		while ((*env_str) != '\0')
		{
			tmp_line = ft_charjoin(new_line, (*env_str));
			if (!tmp_line)
			{
				free(buf);
				return (NULL);
			}
			new_line = tmp_line;
			env_str++;
		}
		free(buf);
		return (new_line);
	}
	return (new_line);
}
