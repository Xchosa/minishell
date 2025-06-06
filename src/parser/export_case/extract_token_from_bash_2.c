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


char *handle_mulit_token(char *line)
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

void tokenise_muliple_tok_from_env(t_token **token_lst, t_token *prev_token)
{
    t_token *split_token;
    t_token *connect_token;
    if(multiple_tokens((*token_lst)->token) == false)
        return ;
    split_token = tokeniser((*token_lst)->token);
	if(*token_lst == (*token_lst)->head && (*token_lst)->next == NULL)
	{
		clean_token_lst(*token_lst);
		*token_lst = split_token;
		
	}
	else
	{
		if((*token_lst)->next)
			connect_token = (*token_lst)->next;
		else
			connect_token = NULL;
		prev_token->next = split_token;
		split_token = tokenlast(split_token);
		split_token->next = connect_token;
	}
}
// error cases:
/*

minishell:$ $h outifle

 tokeniser 

| token: '$h' | token_type: 12 
| token: 'outifle' | token_type: 0 
before tokensise mulitple
| token: 'ls -al >' | token_type: 12 
| token: 'outifle' | token_type: 0 
do i come here?
minishell:$ $h
minishell:$ $h

 tokeniser 

| token: '$h' | token_type: 12 
before tokensise mulitple
| token: 'ls -al >' | token_type: 12 
do i come here?
after tokensise mulitple
| token: 'ls' | token_type: 0 
| token: '-al' | token_type: 0 
| token: '>' | token_type: 4 
split_token
| token: 'ls' | token_type: 0 
| token: '-al' | token_type: 0 
| token: '>' | token_type: 4 
split_token
| token: '-al' | token_type: 0 
| token: '>' | token_type: 4 
split_token
| token: '>' | token_type: 4 

 append token string in export 

| token: '' | token_type: 12 
*/