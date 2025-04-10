/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/10 16:29:57 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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