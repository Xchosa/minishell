/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:11 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/14 09:28:56 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_token_lst_and_line(t_token *token_lst, char *line)
{
	if (token_lst)
		clean_token_lst(token_lst);
	(void)line;
}

void	clean_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	if (!token_lst)
		return ;
	while (token_lst)
	{
		tmp = token_lst->next;
		free(token_lst->token);
		free(token_lst);
		token_lst = tmp;
	}
}

void	free_single_token(t_token **token)
{
	if (*token)
	{
		if ((*token)->token)
			free((*token)->token);
		free(*token);
		*token = NULL;
	}
}

bool	tokeniser_successful(t_token *token_lst, char *line)
{
	if (!token_lst)
	{
		free(line);
		return (false);
	}
	return (true);
}
