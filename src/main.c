/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:22:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:17 by poverbec         ###   ########.fr       */
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
//	t_bash *bash;
// 	t_exit_codes *exit_code;
//	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
//		return(1);

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


// garabe collecter implement
// gc_malloc in einer linked list copieren
// am ende von oben nach unten freen;


void   leaks(void)
{
    printf("\n");
    system("leaks minishelll: \n");
}

// handle: 
//  echo test $? 

int main(int argc, char **argv, char **env)
{
	
    t_token *token_lst;
	(void)argv;
	// t_cmd_list *cmd_lst;
	t_bash *bash;
	atexit(leaks);
    // char *line = "wow \' hallo \" world \' dfo hello";
	char *line = "export h=poverbec";
	// char *line = "echo   hello world <<    \"wow hello\""; // fehler infitite auch mit wow raus 
	// char *line = "export h=\"echo hello test\" "; // fehler gerade
	// char *line = "\'hello< -hello\'echo| ls -l hello l <wow hello";
	// char *line = "\"hello '< \"echo|hello << wow hello";// sollte valid sein
	// char *line = "\'hello \"< \'echo|hello << wow hello";// sollte valid sein
	// char *line = "\"hello< echo|hello << wow hello"; // nicht valid
	
	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
		return(1);
	
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		printf("\n syntax error \n");
		return (1);
	}
	if (lexer_valid_ident(line) == false)
	{
		printf("\n invalid identifer");
		return(1);
	}

	
    token_lst = tokeniser(line);
	{
		// check_here_doc_and_take_exit_word(token_lst);;
		iter_tokenlst(token_lst, &print_tokenlst);

		bash = get_bash();
		printf("\nenv:\n");
		ft_print_array(bash->env);
	}
	//cmd_lst = init_cmd_lst(token_lst);
	
}

//char** cmd = char* token
// ls -l -a | grep a
// das ordnen der tokens - dafur ist der baum da 
// eine token liste und keine cmd liste?
// muss cmd schon geordnet sein?
// ls >infile -l


/*
sturcts
	pipecmd
	listcmd
	backcmd
	execcmd
	redircmd

constructor functions
	pipecmd
	listcmd
	backcmd
	execcmd
	redircmd

*/