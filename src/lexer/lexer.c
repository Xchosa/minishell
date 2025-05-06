/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:32:26 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:17 by poverbec         ###   ########.fr       */
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
// fumction to check if there is uneven nbr of 
// /* 


bool	lexer(char *line)
{
	int i;
	bool syntax;
	
	syntax = true;
	i = 0;
	syntax = wrong_use_pipe_and_redirection(line);
	while(line[i])
	{
		while(line[i])
		{
			if (count_up_strings(line + i) >= 0)
				i += count_up_strings(line + i);
			else
				return(false);
			if (check_for_correct_double_divider(line +i) == false)
				return (false);
			if (check_for_correct_single_divider(line + i) == false)
				return (false);
			i++;
		}
		if(line[i]== '\0')
			break;
		i++;
	}
	return (syntax);
}

bool	lexer_valid_ident(char *line)
{
	int i;
	bool valid_ident;
	
	valid_ident = true;
	i = 0;
	{
		while(line[i])
		{
			skip_whitespace(&line);
			if(export_case(&line) == false)
			{
				get_exit_codes()->last_exit_code = invalid_identifer;
				return (valid_ident = false);
			}
		}
	}
	return (valid_ident);
}
// handle case:     export    g4h="echo test"
// bash-3.2$     export    g4g=echo test
// bash-3.2$ echo $?
// 0
// bash-3.2$     export    4gh='echo test'
// bash: export: `4gh=echo test': not a valid identifier
// bash-3.2$     export    gh='echo test'
// bash-3.2$ echo $gh
// echo test
// bash-3.2$ echo $g4g
// echo

bool export_case(char *line)
{
	int i;

	i = 0;
	if(ft_strncmp("export", line, 6) == 0)
		line + 6;
	else
		return (true);
	skip_whitespace(&line);
	if (ft_isalpha(line[i]) != true)
		return (false);
	line++;
	while(ft_strncmp("=", *line, 1) != 0)
	{
		if(ft_isalnum(line[i]) != true)
			return(false);
		line++;
	}
	line++;
	// sind nach dem = 
	
	
	
	
}
