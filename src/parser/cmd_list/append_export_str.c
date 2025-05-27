/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_export_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:55:01 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/27 10:55:33 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


static bool equal_last(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
    }
    i--;
    if(ft_strncmp((str + i), "=", 1) == 0)
        return true;
    return (false);
}


bool multiple_tokens(char *line)
{
	t_token *cpy_tok;

	if (!line || *line == '\0')
		return(false);

    cpy_tok =tokeniser(line);
    if(cpy_tok == NULL)
    {
        free(cpy_tok);
        return(false);
    }
    if(cpy_tok->next == NULL)
    {
        free(cpy_tok);
        return(false);
    }
    free(cpy_tok);
    return(true);
}


void append_export_str(t_token **curr_token)
{
    t_token *passed_position;

    passed_position = (*curr_token);
    while(*curr_token)
    {
        if ((*curr_token)->token_type == Export_var 
        && (*curr_token)->next 
        && (*curr_token)->next->token_type == TEXT 
        && equal_last((*curr_token)->token) == true)
        {
            if(multiple_tokens((*curr_token)->next->token) == true)
            {
                printf("extend tokens %s + %s \n", (*curr_token)->token, (*curr_token)->next->token);
                char *tmp_char= ft_strdup((*curr_token)->token);
                free((*curr_token)->token);
                (*curr_token)->token = ft_strjoin(tmp_char, (*curr_token)->next->token);
                (*curr_token)->next = (*curr_token)->next->next;
                free(tmp_char);
            }
        }
        (*curr_token) = (*curr_token)->next;
    }      
    (*curr_token) = passed_position;
}
