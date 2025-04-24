/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:32:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 13:44:35 by poverbec         ###   ########.fr       */
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
// fumction to check if there is uneven nbr of \" 

bool	wrong_use_pipe_and_redirection(char *line)
{
	int i;
	int size;
	
	i = 0;
	if ((line[i] == '|')|| (line[i] == '<') || (line[i] == '>') || (line[i] == ';'))
		return (false);
	size = ft_strlen(line);
	if (line [size -1] == '|')
		return (false);
	return(true);
}


bool	uneven_S_and_D_Quotes(char *line)
{
	int i;
	int count_s_quotes;
	int count_d_quotes;

	count_s_quotes = 0;
	count_d_quotes = 0;
	i = 0;
	while(line[i] != '\0')
	{
		if (ft_strncmp("\"", &line[i], 1) == 0)
		{
			count_d_quotes++;
		}
		if ((ft_strncmp("\'", &line[i], 1) == 0))
			count_s_quotes++;
		i++;
	}
	if((count_s_quotes % 2) != 0 )
		return (false);
	if((count_d_quotes % 2) != 0 )
		return (false);
	return (true);
}


bool	lexer(char *line)
{
	if (wrong_use_pipe_and_redirection(line) == false)
		return (false);
	if (uneven_S_and_D_Quotes(line) == false)
		return (false);
	return (true);
}