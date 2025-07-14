/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/14 13:45:38 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

void	leaks(void)
{
    printf("\n");
    system("leaks minishell: \n");
}

int	main(int argc, char **argv, char **env)
{
	bool	tty_shell;
	char	*line;

	tty_shell = false;
	line = NULL;

	if (init_bash(env, argc) == false || (init_exit_codes(argc) == false))
		return (1);

	if (isatty(STDIN_FILENO))
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
	// printf("\nclear history");
	if(tty_shell == true)
		rl_clear_history();
}
