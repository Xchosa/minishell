/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/27 10:30:15 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"



static char *tokenise_divider(char *content, char *new_token)
{
	char *tmp_token;

	int i;
	i = 0;
	while (check_for_divider_without_space(content[i]) == true)
	{
		tmp_token = ft_charjoin(new_token, content[i]);
		free(new_token);
		new_token = tmp_token;
		if(not_single_divider(content[i])== false )
			return(new_token);
		i++;
	}
	return(new_token);
}

char* get_token(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	while (content[i] != '\0' && check_for_divider_with_space(content[i]) == false)
	{
		if (char_is_alpha_nbr_and_no_whitespace(content[i]))
		{	
			tmp_token = ft_charjoin(new_token, content[i]);
            free(new_token);
            new_token = tmp_token;
		}
		if (check_for_divider_with_space(content[i +1 ]) == true)
			return (new_token);
		i++;
	}
	// while (check_for_divider_without_space(content[i]) == true)
	if(check_for_divider_without_space(content[i]) == true)
	{
		// tmp_token = ft_charjoin( new_token, content[i]);
		// free(new_token);
        // new_token = tmp_token;
		// if(not_single_divider(content[i])== false )
		// 	return(new_token);
		// i++;
		new_token = tokenise_divider(content + i, new_token);
	}
	return(new_token);
}

// to do seperate function innerhalb des jeweiligen while loops


t_type get_token_type(char *content)
{
	int i;

	i = 0;
	if(content[i] == '|')
		return(PIPE);
	if (content[i] == '>')
	{
		if (content[i+1] == '>')
			return (Append);
		else
			return(Redirect_output);
	}
	if (content[i] == '<')
	{
		if (content[i+1] == '<')
			return (here_doc);
		else
			return (Redirect_input);
	}
	if(ft_strncmp( "export", content, 6) == 0)
		return (EXPORT);
	return(TEXT);
}
// if (content[i] == '\"') // " // quotes in seperate function with export
	// 	return (D_Quote);
	// if (content[i] == '\'') // '
	// 	return (S_Quote);


t_token*	tokenlast(t_token *lst)
{
	if (lst == NULL)
		return(NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	tokenadd_back(t_token **lst, t_token *new_token)
{
	t_token	*last_node;

	if (new_token== NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		new_token->head = new_token;
		return ;
	}
	else
	{
		last_node = tokenlast(*lst);
		new_token->head = (*lst)->head;
		last_node->next = new_token;
	}
}

t_token *create_token(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token(content);
	new_token->token_type = get_token_type(content);
	new_token->next = NULL;
	return (new_token);
	// tokenadd_back(get_config()->token_list, new_token);
}

t_token	*tokenlstnew(char	*content)
{
	t_token	*token;

	skip_whitespace(&content);
	token = create_first_token(&content);
	if(!token)
		return (NULL);
	token->next = 0;
	token->head = token;
	return (token);
}

t_token *tokeniser(char *line)
{
	t_token *new_token;
	t_token *token_lst;

	if (!line || *line == '\0')
		return(NULL);
	token_lst = tokenlstnew(line);
	if (!token_lst)
		return (NULL);
	line = update_line(line,token_lst);
	new_token = NULL;
	while(*line)
	{
		if (skip_whitespace_and_check_for_eof(&line) == false)
			return(token_lst);
		new_token = create_token_with_quote_case(&line, token_lst);
		tokenadd_back(&token_lst, new_token);
		line = update_line(line, token_lst);
	}
	if(new_token ==NULL)
		return (token_lst);
	new_token->next = NULL;
    
	return (token_lst);
}

