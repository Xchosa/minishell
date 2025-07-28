/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/28 11:56:02 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd(
			"minishell: execute minishell wihtout arguments first", 2);
		return (1);
	}
	line = NULL;
	if (init_bash(env, argc) == false || (init_exit_codes(argc) == false))
		return (1);
	if (isatty(STDIN_FILENO))
	{
		interactive_shell_tty(line);
		rl_clear_history();
	}
	else
		non_interactive_shell();
}
