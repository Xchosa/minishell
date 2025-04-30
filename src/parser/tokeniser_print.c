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

void	print_cmd_lst(t_cmd_list)
{
	int i;

	i = 0;
	printf(" cmd node type head: %d" |, t_cmd_node->head->cmd_type );
	printf("cmd node char arry: \n");
	while(t_cmd_node->head->cmd[i])
	{
		printf("%d. %s | ", i, t_cmd_node->head->cmd[i])
		i++;
	}
	// next zu file list 
}

void	iter_cmdlst(t_cmd_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = t_cmd_node->head->next;
	}
	return ;
}


t_cmd_list	*init_cmd_list(t_token *token_list)
{
	t_cmd_list *cmd_list;
	t_token		*curr_token;

	int cmd_type;
	cmd_list = cmd_list_to_NULL();
	// each type own function
	if(t_token->token_type == TEXT)
	{
		cmd_type = 1;
		
	}


	return(cmd_list);
}

//iter_tokenlst(token_lst, &print_tokenlst);