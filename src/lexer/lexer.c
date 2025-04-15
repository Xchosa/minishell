/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:32:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/15 17:01:29 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
Lexer overview
check for valid input 
e.g. | < > at end, double or beginning

handle ' ""
trim spaces form start and AND inbetween 
if not the same as previous one 
- only then save in history 
(check what is fkt add_history doing)
 (echo    ls does save spaces , ls     -al does not)

check (empty) input (file) check for outfile

get some bash cmds to test 

every token one node 
what is awk


*/


bool	wrong_use_pipe_and_redirection(char *line)
{
	int i;
	int size;
	
	i = 0;
	if ((line[0] == '|')|| (line[0] == '<') || (line[0] == '>') || (line[0] == ';'))
		return (false);
	size = ft_strlen(line);
	if (line [size -1] == '|')
		return (false);
	return(true);
}

bool	lexer(char *line)
{
	if (wrong_use_pipe_and_redirection(line) == false)
		return (false);
	return (true);
}
