/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_to_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 11:05:22 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static	bool	pipe_token(t_token **token_list)
{
	if (*token_list == NULL)
		return (true);
	if ((*token_list)->token_type == PIPE)
	{
		(*token_list) = (*token_list)->next;
		return (true);
	}
	return (false);
}

bool	redir_token(t_token **token_list)
{
	int	type;

	if (*token_list == NULL)
		return (false);
	type = (*token_list)->token_type;
	if (type == Redirect_input || type == Redirect_output
		|| type == Append || type == here_doc)
		return (true);
	else
		return (false);
}

static	void	if_redirect_set_file_node_head(t_file_list *file_list,
	t_file_node **file_node, t_token **token_lst)
{
	file_list->head = process_token_type_redir(token_lst);
	*file_node = file_list->head;
	file_list->size = 1;
	file_list->tail = *file_node;
}

static	void	if_redirect_append_file_node(t_file_list *file_list,
	t_file_node **file_node, t_token **token_lst)
{
	(*file_node)->next = process_token_type_redir(token_lst);
	*file_node = (*file_node)->next;
	file_list->tail = *file_node;
	file_list->size += 1;
}

t_cmd_node	*process_token(t_token **token_lst)
{
	t_cmd_node	*cmd_node;
	t_file_node	*file_node;
	t_file_list	*file_list;

	file_list = file_list_to_null();
	cmd_node = init_cmd_node_null(file_list);
	while (*token_lst)
	{
		process_token_type_text(token_lst, cmd_node);
		if (*token_lst == NULL)
			break ;
		if (pipe_token(token_lst) == true)
			break ;
		if (redir_token(token_lst) == false)
			break ;
		if (file_list->head == NULL)
			if_redirect_set_file_node_head(file_list, &file_node, token_lst);
		else if ((*token_lst)->token_type != PIPE
			&& (*token_lst)->token_type != TEXT)
			if_redirect_append_file_node(file_list, &file_node, token_lst);
	}
	check_cmd_builtin(&cmd_node);
	return (cmd_node);
}
