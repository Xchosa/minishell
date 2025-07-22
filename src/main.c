/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/22 14:58:12 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"


int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argv;
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

// >tmp_out | echo 1 
// seq fault

// cat << $USER

// exit "-100"
// exit -9223372036854775805

// exit ------
// exit -12560
// > out
// awk 'BEGIN{for(i=1;i<=1000000;i++)print int(i)}' | awk '{sum+=$1} END {print sum/NR}'

// "./""ls" 
// .ls

// ./ls

// "./"ls

// "./""ls"

// "./"''"ls"

// 3123

// lsa

// /ls

// EechoE

// /ls/

// /bin/

// /bin/cats

// ./4242424242.sh

// rm -f something

// | echo -n oui

// | | |
// permission denied