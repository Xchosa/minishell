/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/03 14:59:43 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token*	tokenlast(t_token *lst)
{
	if (lst == NULL)
		return(NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	tokenadd_back(t_token **lst, t_token *new_token)
{
	t_token	*last_node;

	if (new_token== NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		new_token->head = new_token;
		return ;
	}
	else
	{
		last_node = tokenlast(*lst);
		new_token->head = (*lst)->head;
		last_node->next = new_token;
	}
}

t_token *create_token(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token(content);
	new_token->token_type = get_token_type(new_token->token);
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenlstnew(char	*content)
{
	t_token	*token;

	skip_whitespace(&content);
	token = create_first_token(&content);
	if(!token)
		return (NULL);
	token->next = 0;
	token->head = token;
	return (token);
}

t_token	*tokeniser(char *line)
{
	t_token *new_token;
	t_token *token_lst;

	if (!line || *line == '\0')
		return(NULL);
	token_lst = tokenlstnew(line);
	if (!token_lst)
		return (NULL);
	line = update_line(line,token_lst);
	new_token = NULL;
	while(*line)
	{
		if (skip_whitespace_and_check_for_eof(&line) == false)
			return(token_lst);
		new_token = create_token_with_quote_case(&line, token_lst);
		tokenadd_back(&token_lst, new_token);
		line = update_line(line, token_lst);
	}
	if (new_token ==NULL)
		return (token_lst);
	new_token->next = NULL;
    
	return (token_lst);
}

