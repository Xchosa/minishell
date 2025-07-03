/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:45 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:07:49 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char* get_export_token(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	while (ft_strncmp("=", content, 1) != 0)
	{
		tmp_token = ft_charjoin(new_token, content[i]);
        free(new_token);
        new_token = tmp_token;
		i++;
	}
	return (new_token);
}

char *update_export_line(char *line)
{
	while((ft_strncmp("=", line, 1) != 0))
	{
		line++;
	}
	line++;
	return (line);
}

t_token *create_export_token(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_export_token(content);
	new_token->token_type = EXPORT;
	new_token->next = NULL;
	return (new_token);
}


t_token *create_token_q_case_and_export(char **line, t_token *token_lst)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return(d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return(s_quote_case(line));
	// if (strcmp("export", token_lst->token)== true)
	if (ft_strncmp("export", token_lst->token, 6) == 0)
	{
		token_lst->token_type = EXPORT;
		return(create_export_token(*line));
	}
	else
		return (create_token(*line));
}




