/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:40:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/22 14:50:21 by poverbec         ###   ########.fr       */
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

// herdoc does not need to update history

void check_here_doc_and_take_exit_word(t_token *token_lst)
{
	char *her_doc_string;
	char *doc_line;
	int len_her_doc_string;

    while(token_lst != NULL)
	{
		if(token_lst->token_type == here_doc)
		{
			token_lst = token_lst->next;
			her_doc_string = ft_strdup(token_lst->token);//no space befor or after
			len_her_doc_string = ft_strlen(her_doc_string);
			while(1)
			{
				doc_line = readline("another heredoc> ");
				if(ft_strncmp(doc_line, her_doc_string, len_her_doc_string) == 0)
					break;
			}
		token_lst = token_lst->next;
		}
	}
}