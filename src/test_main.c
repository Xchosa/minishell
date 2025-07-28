/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:29:52 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/28 12:03:45 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

// int	main(int argc, char **argv, char **env)
// {
//     t_token	*token_lst;
// 	(void)argv;
// 	t_cmd_list *cmd_lst;
// 	t_bash *bash;
//     char *line;
// 	//atexit(leaks);
// 	// char *line = <<1"; // leaked
// 	char *original_line;
//     char *new_line;
// 	line = ft_strdup(" \"\" ");
// 	// line = ft_strdup("echo \" '\"$?\" '\"");
// 	// >outfile | echo 1
// 	// malloc line to extend $XX
// 	// char **temp_content = content;

// 	// char *line = "$h outfile";
//     // char *line = "export t=\"world | around < \" echo world";
//     // line = "echo $?dfdfd"; // = wird falsch gehandelt
// 	// char *line = "echo \"$USER\" echo $USER eoche \'$USER\' ";
// 	// char *line = "echo $h world echo $paul echo $world";
// 	// char *line = "export h=thilo paul=kruecke world=\"cat makefile\" ";
// 	// char *line = "echo $USER $? echo \"$?\"\"$USER\" echo \'$USER\' ";
// 	//char *line = "echo test wc world >outfile test >outfile2 >outfile3";
//     // line = "export var3=\"cat Makefile | grep <\"  ";
//     // line = "export \"Var1\"=\"hello var1\"   
// var3=\"cat Makefile | grep <\"  var2=world  ";
// 	//char *line = "export Var1=hello var=\"cat Makefile | grep <\" ";

// 	//char *line = "cat < infile > outfile > out3file";// sollte valid sein
// 	//char *line = "\'hello \"< \'echo|hello << wow hello";// sollte valid sein
// 	// char *line = "\"hello< echo|hello << wow hello"; // nicht valid
// 	(void)argc;

// 	if (init_bash(env, 1 )== false || (init_exit_codes(1) == false))
// 		return(1) ;
// 	if (init_bash(env, 1 )== false || (init_exit_codes(1) == false))
// 		return(1) ;

// 	if (check_lexer_and_free(line) == false)
// 		return (1);

// 	(void)bash;
// 	printf("original line: %s \n" , line);
// 	new_line = extend_line(&line);
// 	printf("New_line: %s \n" , new_line);
//     original_line = new_line;
// 	token_lst = tokeniser(&new_line);

// 	if (!token_lst)
//     {
// 		printf("error tokeniser\n");
// 		return (1);
// 	}
// 	iter_tokenlst(token_lst, &print_tokenlst);

// 	// printf("\nenv:\n");
// 	// 	ft_print_array(bash->env);

// 	// if(extend_env(token_lst)== true)
// 	// 	return(1);

// 	// printf("\n export_list:\n\n");
// 	// extends $h to word if saved in env 
// 	// token_lst = extend_saved_export_var(&token_lst);
// 	// change_only tokenise if CALL_SAVED_VAR

// 	// iter_tokenlst(token_lst, &print_tokenlst);
// 	// printf("\n multiple tokens split:\n\n");

// 	// splited saved_var erneut mit tokeniser
// 	// printf("\n append token\n\n");
// 	// handle_export(token_lst);
// 	// append_export_str(&token_lst);
// 	if (final_lexer(token_lst, original_line) == false)
// 	{
// 		clean_bash_env();
// 		clean_exit_codes();
// 		delete_tmp_files("/tmp");
// 		rl_clear_history();
// 		return(1);
// 	}
//     if (lexer_token(token_lst, original_line) == false)
// 	{
// 		clean_bash_env();
// 		clean_exit_codes();
// 		delete_tmp_files("/tmp");
// 		rl_clear_history();
// 		return(1);
// 	}
// 	// iter_tokenlst(token_lst, &print_tokenlst);

// 	printf("\ndo i come to cmd list? \n\n");
// 	cmd_lst = init_cmd_list(&token_lst, original_line);
// 	iter_cmd_lst(cmd_lst, &print_cmd_lst);
//     printf("\nis it Thilos issue: \n\n");
// 	ft_execute(cmd_lst, get_bash()->env);

// 	// clean_cmd_list_objects_tmp_files(cmd_lst);

// }
