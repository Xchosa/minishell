/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/14 16:34:36 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


void loop_until_space_or_operator(char **line)
{
	while(*line)
	{
		if(ft_strchr("\t\n\v\f\r" , **line) == NULL)
			break;
		(*line)++;
	}
}

char* get_token(char *content)
{
	int i;

	i = 0;
	char new_token;
	while(content[i] != NULL)
	{
		if (ft_isalnum(content[i]) != NULL)
			new_token = content[i];
		else if(ft_strchr ("|", content[i]) == NULL)
			break;
		else if(ft_strchr ("\t\n\v\f\r", content[i]) == NULL)
			break;
		i++;
	}
	return(new_token);
}

t_type *get_token_type(char *content)
{
	int i;

	i = 0;
	if(content[i] == '|')
		return(PIPE);
	if (content[i] == '>')
		return(Redirect_output);
	if (content[i] == '<')
		return(Redirect_input);
	if (content[i] == 34) // " 
		return (Quote);
	if (content[i] == 39) // '
		return(Quote);
	// heredoc?
	else
		return(TEXT);
	
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
		last_node = ft_lstlast(*lst);
		last_node->next = new_token;
	}
}

t_token *create_token(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token_type = get_token_type(content);
	new_token->token = get_token(content);
	new_token->next = NULL;
	tokenadd_back(get_config()->token_list, new_token);
}

// get_config init

bool tokeniser(char *line)
{
	t_token *new_token;
	
	while(*line)
	{
		loop_until_space_or_operator(&line);
		new_token = create_token(&line);
		line = update_line(&line);
		// typ txt ls (value) // 
		// create_nodes(line, ); // cmd_node mit typ und value 
	}
	return (true);
}
