/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/15 16:19:01 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*tokenlast(t_token *lst)
{
	t_token	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current != NULL && current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

bool	tokenadd_back(t_token **lst, t_token *new_token)
{
	t_token	*last_node;
	bool	tokeniser_worked;

	if (new_token == NULL)
	{
		return (tokeniser_worked = false);
	}
	if (*lst == NULL)
	{
		*lst = new_token;
		new_token->head = new_token;
		return (false);
	}
	else
	{
		last_node = tokenlast(*lst);
		new_token->head = (*lst)->head;
		last_node->next = new_token;
		new_token->next = NULL;
		return (true);
	}
}

void	set_last_node_null(t_token **lst)
{
	t_token	*last_node;

	last_node = tokenlast(*lst);
	last_node->next = NULL;
	return ;
}

t_token	*create_token(char **content)
{
	t_token	*new_token;

	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = get_token(content);
	new_token->token_type = get_token_type(new_token->token);
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenlstnew(char	**content)
{
	t_token	*token;

	skip_whitespace(content);
	if ((**content) == '\0')
		return (NULL);
	token = create_first_token(content);
	if (!token)
		return (NULL);
	token->next = NULL;
	token->head = token;
	return (token);
}



t_token	*tokeniser(char **line)
{
	t_token		*new_token;
	t_token		*token_lst;

	if (!line || **line == '\0')
		return (NULL);
	token_lst = tokenlstnew(line);
	if (!token_lst)
		return (NULL);
	new_token = NULL;
	while (*line && **line != '\0')
	{
		if (skip_whitespace_and_check_for_eof(line) == false)
			break ;
		new_token = create_token_with_quote_case(line, token_lst);
		if (tokenadd_back(&token_lst, new_token) == false)
		{
			if (new_token)
                free_single_token(&new_token);
			clean_token_lst(token_lst);
			return (NULL);
		}
	}
	return (token_lst);
}

