/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 13:23:42 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"


// int	main(int argc, char **argv, char **envp)
// {
// 	(void) argv;
// 	(void) argc;
// 	(void) envp;
// 	bool	tty_shell;
	
// 	tty_shell = false;
// 	char *line;
	
// 	line = NULL;

// 	if(isatty(STDIN_FILENO))
// 	{
// 		interactive_shell_tty(argc, argv, envp, line);
// 		tty_shell = true;
// 	}
// 	else
// 		non_interactive_shell(argc, argv, envp, line);
// 	// write form terminal into line (interaktiv oder aktiv )
// 	// line = get_input_from_tty_or_not(argc, argv, line);

// 	// 1. laxxen
// 	// 2. parsen
// 			// tree 
// 	// 3. executen
// 	if (tty_shell == true)
// 		printf("clean history function + destroy shell");
// }

int main()
{
    t_token *token_lst;
    // char *line = "hello< echo|hello << wow";
	char *line = "\"hello< \"echo|hello << wow hello";
	
    token_lst = tokeniser(line);
	{
		iter_tokenlst(token_lst, &print_tokenlst);
	}
}