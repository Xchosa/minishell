/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:25:55 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 10:16:38 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	d_quote_case_no_div(char *line)
{
	int	i;

	i = 1;
	while (ft_strncmp("\"", line, 1) != 0)
	{
		if (line[i])
			return (false);
		if (check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
	i++;
	while (line[i])
	{
		skip_whitespace(&line);
		if (check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
	return (true);
}

bool	check_syntax_heredoc(char *heredoc_del)
{
	int	i;

	i = 0;
	while (heredoc_del[i])
	{
		if (ft_strchr(".!?-@#$^&*(){}", heredoc_del[i]) != NULL)
			return (false);
		i++;
	}
	return (true);
}

bool	check_for_cmd(t_token *token)
{
	if (token->token_type == Redirect_input)
		return (true);
	else if (token->token_type == Redirect_output)
		return (true);
	else if (token->token_type == Append)
		return (true);
	else if (token->token_type == here_doc)
		return (true);
	return (false);
}
