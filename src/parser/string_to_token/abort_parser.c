/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:08:01 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/02 17:58:05 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_token(t_token **token_list)
{
	t_token	*next_token;
	t_token	*delete_token;

	if (!token_list || !(*token_list))
		return ;
	delete_token = *token_list;
	while (delete_token)
	{
		next_token = delete_token->next;
		free(delete_token->token);
		free(delete_token);
		delete_token = next_token;
	}
	*token_list = NULL;
}
