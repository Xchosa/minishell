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

void	iter_tokenlst(t_token *lst, void (*f)(t_token *))
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
	return ;
}


//iter_tokenlst(token_lst, &print_tokenlst);