/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/15 17:44:50 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


void skip_whitespace(char **line)
{
	while(*line)
	{
		if(ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break;
		(*line)++;
	}
}

bool	check_for_divider(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (false);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (false);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (false);
	if (ft_strncmp (">", &c, 1) == 0)
		return (false);
	if (ft_strncmp (";", &c, 1) == 0)
		return (false);
	return (true);
}

char* get_token(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	// tmp_token = NULL;
	while (content[i] != '\0')
	{
		if (ft_isalnum(content[i]) != 0)
		{	
			tmp_token = ft_strjoin(new_token, &content[i]);
            
            // Free the old string
            free(new_token);
            
            // Update new_token to point to the new string
            new_token = tmp_token;
			
			
			// tmp_token = new_token;
			// free(new_token);
			// new_token = ft_strjoin(tmp_token, &content[i]);
			// free(tmp_token);
		}
		else if (check_for_divider(content[i]) == false)
			break ;
		i++;
	}
	return(new_token);
}

t_type get_token_type(char *content)
{
	int i;

	i = 0;
	if(content[i] == '|')
		return(PIPE);
	if (content[i] == '>')
		return(Redirect_output);
	if (content[i] == '<')
		return(Redirect_input);
	if (content[i] == '"') // " 
		return (D_Quote);
	if (content[i] == '\'') // '
		return(S_Quote);
	// heredoc == <<  
	 // 
	else
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
	token = malloc (sizeof(t_token));
	token = create_token(content);
	if(!token)
		return (NULL);
	token->next = 0;
	return (token);
}

char	*update_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (check_for_divider(line[i])== false)
			break;
		i++;
	}
	return	(&line[i]);
}

t_token *tokeniser(char *line)
{
	t_token *new_token;
	t_token *token_lst;
	token_lst = tokenlstnew(line);
	if (!token_lst)
		return (false);
	while(*line)
	{
		skip_whitespace(&line);
		new_token = create_token(line);
		tokenadd_back(&token_lst, new_token);
		line = update_line(line);
		printf("line: %s\n", line);
	}
	
	// iter_tokenlst(token_lst, &print_tokenlst);
	return (token_lst);
}
