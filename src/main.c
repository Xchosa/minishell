/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/10 10:44:47 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) argc;
	(void) envp;
	
	char *line;


	if(isatty(STDIN_FILENO))
	{
		while(1)
		{
		// command holen
		line = readline("Paul's coole bash: ");
		add_history(line);
		}
	}
		else 
			printf("get_next_history callen\n");
	
	tokeniser(line);
	
	// 1. laxxen
	// 2. parsen
	// 3. executen


	
	// if tty_shell
	// history clearen 
	//destroy_shell()
	printf("main function");
}

bool tokeniser (char *line)
{
	
}
