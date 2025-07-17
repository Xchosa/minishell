/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_chars_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:35:48 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/14 10:14:31 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token	*validate_token_str(t_token **new_token)
{
	if (!new_token)
		return (NULL);
	if (!(*new_token))
		return (NULL);
	if (!(*new_token)->token)
	{
		free_single_token(new_token);
		return (NULL);
	}
	return ((*new_token));
}

// fur d_quote case
int	process_content_to_token(char **line, t_token *token_node)
{
	int		i;
	char	*tmp_token;

	i = 0;
	// if ((*line)[i] == '\'')
	// 	(*line)++;
	// else if ((*line)[i] == '\"')
	// 	(*line)++;
	// while ((*line)[i] && (*line)[i] != '\"' && (*line)[i] != '\'')
	while ((*line)[i] && (*line)[i] != '\"')
	{
		tmp_token = ft_charjoin(token_node->token, (*line)[i]);
		if (!(*tmp_token))
			return (-1);
		token_node->token = tmp_token;
		(*line)++;
	}
	(*line)++;
	return (i);
}



