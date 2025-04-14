/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/14 16:27:08 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_config* get_config(void) {
	static t_config config;
	return &config;
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) argc;
	(void) envp;
	bool	tty_shell;
	
	tty_shell = false;
	char *line;
	
	line = NULL;

	if(isatty(STDIN_FILENO))
	{
		interactive_shell_tty(argc, argv, envp, line);
		tty_shell = true;
	}
	else
		non_interactive_shell(argc, argv, envp, line);
	// write form terminal into line (interaktiv oder aktiv )
	// line = get_input_from_tty_or_not(argc, argv, line);

	// 1. laxxen
	// 2. parsen
	// 3. executen
	if (tty_shell == true)
		printf("clean history function + destroy shell");
}
