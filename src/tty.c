/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/15 10:57:36 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	while(1)
	{
		// command holen
		line = readline("Paul's coole bash: ");
		add_history(line);
		if(lexer(line) == false)
		{
			printf("fehler lexer");
			return ;
		}
		if (tokeniser(line)== false)
		{
			printf("tokeniser broken\n");
		}
	}
}

void	non_interactive_shell(int argc, char **argv, char **envp ,char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	
	printf("in the non interactive shell\n");
	line = get_next_line(STDIN_FILENO);
	if(lexer(line) == false)
	{
		printf("fehler lexer");
		return ;
	}
}