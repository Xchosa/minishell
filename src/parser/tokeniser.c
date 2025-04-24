/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 11:23:20 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


char* get_token(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	while (content[i] != '\0' && check_for_divider(content[i]) == false)
	{
		if (char_is_alpha_nbr_and_no_whitespace(content[i]))
		{	
			tmp_token = ft_charjoin(new_token, content[i]);
            free(new_token);
            new_token = tmp_token;
		}
		if (check_for_divider(content[i +1 ]) == true)
			return (new_token);
		i++;
	}
	while (check_for_divider(content[i]) == true)
	{
		tmp_token = ft_charjoin( new_token, content[i]);
		free(new_token);
        new_token = tmp_token;
		i++;
	}
	return(new_token);
}

//&& content[i] != ' ')

//To do: 
// sobald " " alles darin als string 

// wenn double quote " h " a" l"
// h a l 

// " 'al; "



t_type get_token_type(char *content)
{
	int i;

	i = 0;
	if(content[i] == '|')
		return(PIPE);
	if (content[i] == '>')
		return(Redirect_output);
	if (content[i] == '<')
	{
		if (content[i+1] == '<')
			return (here_doc);
		else
			return (Redirect_input);
	}
	if (content[i] == '"') // " 
		return (D_Quote);
	if (content[i] == '\'') // '
		return(S_Quote);
	return(TEXT);
	
}

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
		return ;
	}
	else
	{
		last_node = tokenlast(*lst);
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
	if (ft_strncmp("\"", content, 1) == 0)
		token = quote_case(&content);
	else
		token = create_token(content);
	if(!token)
		return (NULL);
	token->next = 0;
	return (token);
}

t_token	*quote_case(char **line)
{
	int i;
	char *tmp_token;
	t_token *new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
	return (NULL);
	new_token->token =ft_strdup("\"");
	(*line)++;
	while((*line)[i] != '"')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
		free(new_token->token);
        new_token->token = tmp_token;
		i++;
	}
	tmp_token = ft_charjoin(new_token->token, (*line)[i]);
	free(new_token->token);
    new_token->token = tmp_token;
	i++;
	
	// *line += i;
	new_token->token_type = TEXT;
	return (new_token);
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
	line = update_line(line); // needs to update until next \" if it points to a \" 
	while(*line)
	{
		skip_whitespace(&line);
		// if (ft_strncmp("\"", &line, 1) == 0)
		// 	new_token = quote_case(line);
		// else
		new_token = create_token(line);
		tokenadd_back(&token_lst, new_token);
		line = update_line(line);
	}
	return (token_lst);
}

