/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/10 16:31:36 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

bool	wrong_use_pipe_and_redirection(char *line)
{
	int i;
	int size;
	
	i = 0;
	if ((line[0] == '|')|| (line[0] == '<') || (line[0] == '>'))
		return (false);
	size = ft_strlen(line);
	if (line [size -1] == '|')
		return (false);
	printf("lexer is working");
	return(true);
}

bool	lexer(char *line)
{
	if (wrong_use_pipe_and_redirection(line) == false)
		return (false);
	return (true);
}

bool	tokeniser(char *line)
{
	// t_tokens t_tokens;
	(void) line;
	// ft_split(line, ' ');
	return (true);
}


