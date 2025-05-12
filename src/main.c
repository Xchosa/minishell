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


// void   leaks(void)
// {
//     printf("\n");
//     system("leaks minishelll: \n");
// }

// handle: 
//  echo test $? 

bool print_error_message(char *line)
{
	int error;
	bool exit_minishell;
	exit_minishell = true;
	error = get_exit_codes()->last_exit_code;
	if (error == invalid_identifier)
		(printf("minishell: '%s': not a valid identifier", line));
	if (error == syntax_failure)
		(printf("minishell: '%s': syntax failure ", line));
	if (error == ec_sucess)
		return(exit_minishell = false);
	return(exit_minishell);
}

int main(int argc, char **argv, char **env)
{
	
    t_token *token_lst;
	(void)argv;
	// t_cmd_list *cmd_lst;
	t_bash *bash;
	//atexit(leaks);
	// char *line = "wow -l";
	//char *line = "export h=echo echo=hello world=\"cat makefile\" hello";
	// char *line = "echo $hallo";
	char *line = "export \"Var1\"=\"hello var1\"     var2=world     var3=\"cat Makefile | grep <\"";
	//char *line = "export Var1=hello var=\"cat Makefile | grep <\" ";
	// char *line = "echo   hello world <<    \"wow hello\""; // fehler infitite auch mit wow raus 
	// char *line = "export h=\"echo hello test\" "; // fehler gerade
	//char *line = "\'hello< -hello\'echo| ls -l hello l <<wow hello";
	// char *line = "\"hello '< \"echo|hello << wow hello";// sollte valid sein
	//char *line = "\'hello \"< \'echo|hello << wow hello";// sollte valid sein
	// char *line = "\"hello< echo|hello << wow hello"; // nicht valid
	
	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
		return(1);
	
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		print_error_message(line);
		return(1);
	}

	// if (lexer_valid_ident(line) == false) // lexer seperate testen
	// {
	// 	print_error_message(line);
	// 	return(1);
	// }

	
    token_lst = tokeniser(line);
	iter_tokenlst(token_lst, &print_tokenlst);
	printf("export_list:\n\n");
	handle_export(token_lst);
	{
		// check_here_doc_and_take_exit_word(token_lst);;
		iter_tokenlst(token_lst, &print_tokenlst);
		bash = get_bash();
		(void)bash;
		if((print_error_message(line)) == true)
			return(1);
			
		printf("\nenv:\n");
		ft_print_array(bash->env);
	}
	//cmd_lst = init_cmd_lst(token_lst);
	
}
