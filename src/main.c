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





// int	main(int argc, char **argv, char **env)
// {
// 	bool	tty_shell;
	
// 	tty_shell = false;
// 	char *line;
	
// 	line = NULL;

// 	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
// 		return(1);

// 	if(isatty(STDIN_FILENO))
// 	{
// 		interactive_shell_tty(argc, argv, env, line);
// 		tty_shell = true;
// 	}
// 	else
// 	{
// 		non_interactive_shell(argc, argv, env, line);
// 		{
// 			if (tty_shell == true)
// 			printf("clean history function + destroy shell");
// 		}
// 	}
// }



// void   leaks(void)
// {
//     printf("\n");
//     system("leaks minishelll: \n");
// }

// discard export hadle if t

int main(int argc, char **argv, char **env)
{
	
    t_token *token_lst;
	(void)argv;
	t_cmd_list *cmd_lst;
	t_bash *bash;
	//atexit(leaks);
	// char *line = "export halloworld=hello juliaworld=world"; // = wird falsch gehandelt
	char *line ="echo $halloworld echo $USER eche juliaworld";
	// char *line = "echo $h world echo $paul echo $world";
	// char *line = "export h=thilo paul=kruecke world=\"cat makefile\" ";
	//char *line = "echo $USER $? echo \"$?\"\"$USER\" echo \'$USER\' ";
	//char *line = "echo test wc world >outfile test >outfile2 >outfile3";
	// char *line = "export \"Var1\"=\"hello var1\"     var2=world     var3=\"cat Makefile | grep <\"";
	//char *line = "export Var1=hello var=\"cat Makefile | grep <\" ";
	// char *line = "echo   hello world <<    \"wow hello\""; // fehler infitite auch mit wow raus 
	// char *line = "ls -al | grep libft  | wc > outfile > out3file";
	//char *line = "cat < infile | grep test | wc > outfile > out3file";
	//char *line = "cat < infile > outfile > out3file";// sollte valid sein
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

	bash = get_bash();
	(void)bash;
	
    token_lst = tokeniser(line);
	iter_tokenlst(token_lst, &print_tokenlst);
	
	// printf("\nenv:\n");
	// 	ft_print_array(bash->env);
	
	if(extend_env(token_lst)== true)
		return(1);

	extend_saved_export_var(token_lst);
	printf("\n export_list:\n\n");
	// change_only tokenise if CALL_SAVED_VAR
	
	iter_tokenlst(token_lst, &print_tokenlst);
	// printf("\n multiple tokens split:\n\n");
	handle_export(token_lst);
	printf("\n called form:\n\n");
	iter_tokenlst(token_lst, &print_tokenlst);
	printf("\ndo i come here:\n\n");
	cmd_lst = init_cmd_list(&token_lst);
	iter_cmd_lst(cmd_lst, &print_cmd_lst);
}
