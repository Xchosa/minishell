/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_from_bash_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:14 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:42:34 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


char    *handle_mulit_token(char *line)
{
    while (*line && (ft_isalnum(*line) || special_char_no_divider_no_eq(*line)))
        line++;
    return (line);
}

char *skip_divider_without_space(char *line)
{
	if (ft_strncmp ("|", line, 1) == 0)
		line++;
	else if(ft_strncmp ("<", line, 1) == 0)
	{
        line++;
        if(ft_strncmp ("<", line, 1) == 0)
            line++;
    }
	else if (ft_strncmp (">", line, 1) == 0)
	{
        if(ft_strncmp (">", line, 1) == 0)
            line++;
    }
	else if (ft_strncmp (";", line, 1) == 0)
		line++;
	return (line);
}

void set_head_for_all_tokens(t_token *token_lst, t_token *head)
{
    t_token *current;

    current = token_lst;
    while (current)
    {
        current->head = head;
        current = current->next;
    }
}

void handle_first_token(t_token **token_lst)
{
    t_token *split_token;
    t_token *connect_token;
    t_token *head_split;

    split_token = tokeniser((*token_lst)->token);
    head_split = split_token;
    connect_token = (*token_lst)->next;
    split_token = tokenlast(split_token);
    free_single_token(token_lst);
    split_token->next = connect_token;
    *token_lst = head_split;
    if (connect_token)
        set_head_for_all_tokens(connect_token, head_split);
}
void handle_next_token(t_token **token_lst, t_token *prev_token)
{
    t_token *split_token;
    t_token *connect_token;

    // split_token = tokeniser((*token_lst)->token);
    char *token_copy = ft_strdup((*token_lst)->token);
    split_token = tokeniser(&token_copy);


    connect_token = (*token_lst)->next;
    prev_token->next = split_token;
    split_token = tokenlast(split_token);
    split_token->next = connect_token;
    set_head_for_all_tokens(split_token, prev_token->head);
    if (connect_token)
        set_head_for_all_tokens(connect_token, prev_token->head);
    free(token_copy);
}

void tokenise_muliple_tok_from_env(t_token **token_lst, t_token *prev_token)
{
    if (multiple_tokens((*token_lst)->token) == false)
        return;   
    if (prev_token == NULL)
        handle_first_token(token_lst);
    else
        handle_next_token(token_lst, prev_token);
}

