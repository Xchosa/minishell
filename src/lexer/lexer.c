/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:32:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/07 13:43:32 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
Lexer overview
check for valid input 
e.g. | < > at end, double or beginning

handle single and doulble quotes 
single quoutes within a double quote string is a normal text no 
error and the other way around
trim spaces form start and AND inbetween 
if not the same as previous one 
- only then save in history 
(check what is fkt add_history doing)
 (echo    ls does save spaces , ls     -al does not)


check (empty) input (file) check for outfile

get some bash cmds to test 



*/
// fucction to check if the single or double quotes are set correct  
// /* 
// missing: ddf>< or dfd <  > ->redirections stright afterwards or > | 

bool	lexer(char *line)
{
	int		i;
	bool	syntax;

	syntax = true;
	i = 0;
	syntax = wrong_use_pipe_and_redirection(line);
	while (line[i])
	{
		while (line[i] != '\0')
		{
			if (count_up_strings(line + i) >= 0)
				i += count_up_strings(line + i);
			else
				return (false);
			if (check_for_correct_double_divider(line + i) == false)
				return (false);
			if (check_for_correct_single_divider(line + i) == false)
				return (false);
			if (lexer_error_chars(line))
				return (false);
			i++;
		}
		// if (line[i] == '\0')
		// 	break ;
		// i++;
	}
	return (syntax);
}


bool	lexer_error_chars(char *line)
{
	while (line)
	{
		if (ft_strchr("+-!@#$^&*;()_={}'.,", (*line)) == NULL)
			return (false);
		line++;
	}
	return (true);
}
