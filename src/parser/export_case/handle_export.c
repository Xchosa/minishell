/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:15:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/27 10:58:39 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"


bool check_for_equal_sign(t_token *current_token)
{
    int i;

    i = 0;
    while(current_token->token[i])
    {
        if (ft_strncmp ("=", &current_token->token[i], 1) == 0)
		    return (true);
        i++;
    }
    return(false);
}


t_token	*split_token_in_sub_token(t_token *current_token, t_token *chain)
{
    t_token *sub_token;
    t_token *head_subtoken;
    t_token *main_token_lst;

    main_token_lst = current_token->next;

    // sub_token = tokeniser(&current_token->token);
    char *token_copy = ft_strdup(current_token->token);
    sub_token = tokeniser(&token_copy);
    if (!sub_token)
        return (main_token_lst);

    head_subtoken= sub_token;
    while (sub_token->next)
        sub_token = sub_token->next;
    sub_token->next = chain;
    free(token_copy);
    return (head_subtoken);
}

t_token	*create_token_splited(char **content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token(content);
	new_token->token_type = get_token_type(content);
	new_token->next = NULL;
	return (new_token);
}

void delete_token(t_token *delete_token)
{
    if (delete_token == NULL)
        return;
    free(delete_token->token);
    free(delete_token);
}


static bool check_for_multi_tokens(char *line)
{
    bool    multiple_token;
	t_token *token_lst;

	if (!line || *line == '\0')
		return(false);
	// token_lst = tokenlstnew(line);
    char *line_copy = ft_strdup(line);
    token_lst = tokenlstnew(&line_copy);
	if (!token_lst)
    {
        free(line_copy);
		return (false);
    }
    skip_whitespace(&line);
    line = handle_special_characters(line);
	if (line == NULL || *line == '\0')
        multiple_token = false;
    else
        multiple_token = true;
    free(token_lst);
    free(line_copy);
	return (multiple_token);
}


bool split_needed(t_token **t_lst)
{
    t_token *check;
    check = (*t_lst);

    if (check_for_multi_tokens(check->token) == true)
        return (true);
    return(false);

}

// out of $hallo 
// typ is saved_var and it is a string-> ist splits eg." ls -al | grep  < makefile" into tokens
void handle_export(t_token *token_lst)
{
    t_token *node_to_delete;
    t_token *node_to_jump_after;
    t_token *new_tokens;

    while(token_lst)
    {
        if(token_lst->token_type == CALL_SAVED_VAR && split_needed(&token_lst)== true)
        {
            node_to_delete = token_lst->next;
            if(token_lst->next->next)
                node_to_jump_after = NULL;
            else
                node_to_jump_after = token_lst->next->next;
            new_tokens = split_token_in_sub_token(token_lst->next, node_to_jump_after);
            delete_token(node_to_delete);
            token_lst->next = new_tokens;
            while(token_lst && token_lst->next && node_to_jump_after != NULL)
            {
                if(token_lst != node_to_jump_after)
                    token_lst= token_lst->next;
            }
        }
        token_lst = token_lst->next;
    }
}
