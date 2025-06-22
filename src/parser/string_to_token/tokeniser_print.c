/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:40:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/30 09:54:54 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void print_tokenlst(t_token *data)
{
	printf("| token: '%s' | token_type: %u \n",data->token, data->token_type);
}

// void print_tokenlst(t_token *data)
// {
// 	printf("| token: '%s' | token_type: %u  | head_token: %s\n",data->token, data->token_type, data->head->token);
// }

void	iter_tokenlst(t_token *lst, void (*f)(t_token *))
{
	t_token *cpy_token;

	cpy_token =lst;
	if (cpy_token == NULL)
		return ;
	while (cpy_token)
	{
        f(cpy_token);
        cpy_token = cpy_token->next;
	}
	return ;
}
