/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/21 16:31:30 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

void   leaks(void)
{
    printf("\n");
    system("leaks minishelll: \n");
}

int	main(int argc, char **argv, char **env)
{
	bool	tty_shell;
	
	tty_shell = false;
	char *line;
	
	line = NULL;

	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
		return(1);

	if(isatty(STDIN_FILENO))
	{
		interactive_shell_tty(argc, argv, env, line);
		tty_shell = true;
	}
	else
	{
		non_interactive_shell(argc, argv, env, line);
		{
			if (tty_shell == true)
			printf("clean history function + destroy shell");
		}
	}
}








