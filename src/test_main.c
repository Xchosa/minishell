/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:29:52 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 11:45:52 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

int	main(int argc, char **argv, char **env)
{
    t_token	*token_lst;
	(void)argv;
	t_cmd_list *cmd_lst;
	t_bash *bash;
    char *line;
	//atexit(leaks);
	// char *line = <<1"; // leaked

    // to do: tokeniser
	line = "echo $T";

	// malloc line to extend $XX
	// char **temp_content = content;

	// char *line = "$h outfile";
    // char *line = "export t=\"world | around < \" echo world";
    // line = "echo $?dfdfd"; // = wird falsch gehandelt
	// char *line = "echo \"$USER\" echo $USER eoche \'$USER\' ";
	// char *line = "echo $h world echo $paul echo $world";
	// char *line = "export h=thilo paul=kruecke world=\"cat makefile\" ";
	// char *line = "echo $USER $? echo \"$?\"\"$USER\" echo \'$USER\' ";
	//char *line = "echo test wc world >outfile test >outfile2 >outfile3";
    // line = "export var3=\"cat Makefile | grep <\"  ";
    // line = "export \"Var1\"=\"hello var1\"      var3=\"cat Makefile | grep <\"  var2=world  ";
	//char *line = "export Var1=hello var=\"cat Makefile | grep <\" ";
	//char *line = "   echo   $hello world >outfile  >out3file  \"wow hello\"   "; // muss wow hello an world hengen;
	// char *line = "export split=\'hallo world\' welt echo world h=hallo w=bello welt";
	// char *line = "ls -al| grep libft  |wc\"d d < ;p\">> hallo > outfile > out3file";
	// char *line = "echo \"hello \'$USER\' Paul mein name ist\" >stand_out"; /// nicht funktioniert 
	//char *line = "cat < infile > outfile > out3file";// sollte valid sein
	//char *line = "\'hello \"< \'echo|hello << wow hello";// sollte valid sein
	// char *line = "\"hello< echo|hello << wow hello"; // nicht valid

	
	if (init_bash(env, argc)== false || (init_exit_codes(argc) == false))
		return(1);
	
	if (check_lexer_and_free(line) == false)
		return (1);

	// if (lexer_valid_ident(line) == false) // lexer seperate testen
	// {
	// 	print_error_message(line);
	// 	return(1);
	// }

	bash = get_bash();
	(void)bash;
	// vor dem tokeinser $h aufloesen und eintauschen // node update weg
    token_lst = tokeniser(&line);
	// free(line);
	if (!token_lst)
    {
		printf("error tokeniser\n");
		return (1);
	}
	iter_tokenlst(token_lst, &print_tokenlst);

	// printf("\nenv:\n");
	// 	ft_print_array(bash->env);
	
	// if(extend_env(token_lst)== true)
	// 	return(1);

	printf("\n export_list:\n\n");
	// extends $h to word if saved in env 
	token_lst = extend_saved_export_var(&token_lst);
	// change_only tokenise if CALL_SAVED_VAR
	
	iter_tokenlst(token_lst, &print_tokenlst);
	// printf("\n multiple tokens split:\n\n");
    
	// splited saved_var erneut mit tokeniser
	printf("\n append token\n\n");
	// handle_export(token_lst);
	append_export_str(&token_lst);
	printf("line , %s \n", line);
    if (lexer_token(token_lst) == false)
    {
		print_error_message(&token_lst, line);
		return(1);
    }
	iter_tokenlst(token_lst, &print_tokenlst);

	printf("\ndo i come to cmd list? \n\n");
	cmd_lst = init_cmd_list(&token_lst, line);
	iter_cmd_lst(cmd_lst, &print_cmd_lst);
    printf("\nis it Thilos issue: \n\n");
	ft_execute(cmd_lst, get_bash()->env);

	clean_cmd_list_objects_tmp_files(cmd_lst);

}












//     printf("\n \nsecond round\n");

//     // new=\"ls -al >;
//     // line = "cat makefile \"$new\" outfile";  works
//     line = "$j > outfile";
//     token_lst = tokeniser(&line);
// 	// free(line);
// 	if (!token_lst)
//         printf("error tokeniser\n");
// 	iter_tokenlst(token_lst, &print_tokenlst);

// 	// printf("\nenv:\n");
// 	// 	ft_print_array(bash->env);
	
// 	// if(extend_env(token_lst)== true)
// 	// 	return(1);

// 	printf("\n export_list:\n\n");
// 	// extends $h to word if saved in env 
// 	token_lst = extend_saved_export_var(&token_lst);
// 	// change_only tokenise if CALL_SAVED_VAR
	
// 	iter_tokenlst(token_lst, &print_tokenlst);
// 	// printf("\n multiple tokens split:\n\n");
    
// 	// splited saved_var erneut mit tokeniser
// 	printf("\n append token\n\n");
// 	// handle_export(token_lst);
// 	append_export_str(&token_lst);
// 	printf("line , %s \n", line);
//     if (lexer_token(token_lst) == false)
//     {
// 		print_error_message(&token_lst, line);
// 		return(1);
//     }
// 	iter_tokenlst(token_lst, &print_tokenlst);

// 	printf("\ndo i come to cmd list? \n\n");
// 	cmd_lst = init_cmd_list(&token_lst, line);
// 	iter_cmd_lst(cmd_lst, &print_cmd_lst);
//     printf("\nis it Thilos issue: \n\n");
// 	ft_execute(cmd_lst, get_bash()->env);

// 	clean_cmd_list_objects_tmp_files(cmd_lst);

// }




/*
ekligste testcases 
echo $?dfdfd
-> print 0 and df
*/