/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:40:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/10 09:47:55 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_tokenlst(t_token *data)
{
	printf("| token: '%s' | token_type: %u \n",data->token, data->token_type);
}

void	iter_tokenlst(t_token *lst, void (*f)(t_token *))
{
	t_token	*cpy_token;

	cpy_token = lst;
	if (cpy_token == NULL)
		return ;
	while (cpy_token != NULL)
	{
		f(cpy_token);
		if (cpy_token->next == NULL) // Add this check
            break ;
		cpy_token = cpy_token->next;
	}
	return ;
}
