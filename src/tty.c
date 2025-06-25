/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/25 10:23:48 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"
#include "signal_tp.h"


/*
Lexer overview
check for valid input 
e.g. | < > at end, double or beginning

handle ' ""
trim spaces form start and AND inbetween 
if not the same as previous one 
- only then save in history 
(check what is fkt add_history doing)
 (echo    ls does save spaces , ls     -al does not)

check (empty) input (file) check for outfile

get some bash cmds to test 

every token one node 
what is awk

*/



static char* read_terminal(void)
{
	char *line;
    init_signal(0); 
	line = readline("minishell:$ ");
	if (line && *line)
        add_history(line);
	if (line == NULL) // Handle EOF (Ctrl+D)
		{
            printf("exit\n");
            exit(get_exit_codes()->last_exit_code);
        }
	return(line);
}

void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)
{
	(void)argc;
	(void)envp;
	(void)argv;
	t_token *token_lst;
	t_cmd_list *cmd_lst;
	while(1)
	{
		line = read_terminal();
		if(check_lexer_and_free(line) == false)
			continue;
		token_lst = tokeniser(line);
		if(tokeniser_successful(token_lst,line) == false)
            continue;
		// printf("\n tokeniser \n\n");
		// iter_tokenlst(token_lst, &print_tokenlst);
		token_lst = extend_saved_export_var(&token_lst);
		append_export_str(&token_lst);
		iter_tokenlst(token_lst, &print_tokenlst);
		if (lexer_token(token_lst) == false)
		{
			print_error_message(line);
			continue;
		}
		cmd_lst = init_cmd_list(&token_lst);
		init_signal(1);
		iter_cmd_lst(cmd_lst, &print_cmd_lst);
		printf("Thilos problem:\n");
		// execute_loop(cmd_lst);// doppel oder nicht 
		ft_execute(cmd_lst, get_bash()->env);
		init_signal(0);
		reset_terminal_state();
		clean_up(line,token_lst); // deleltes tmp files 
	}
	clean_up(line,token_lst);
	// delete_tmp_files;
}

// printf("\n append token string in export \n\n");
// iter_tokenlst(token_lst, &print_tokenlst);
// printf("\n cmd_list works:\n\n");
// iter_cmd_lst(cmd_lst, &print_cmd_lst)


void	non_interactive_shell(int argc, char **argv, char **envp ,char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	t_token 	*token_lst;
	t_cmd_list 	*cmd_lst;

	printf("in the non interactive shell: \n");
	line = get_next_line(STDIN_FILENO);
	if(check_lexer_and_free(line) == false)
		return;
	token_lst = tokeniser(line);
	if(tokeniser_successful(token_lst,line) == false)
            return;
	iter_tokenlst(token_lst, &print_tokenlst);
	token_lst = extend_saved_export_var(&token_lst);
	append_export_str(&token_lst);
	if (lexer_token(token_lst) == false)
		return;
	cmd_lst = init_cmd_list(&token_lst);
	printf("Thilos problem:\n");
	init_signal(1);
	ft_execute(cmd_lst, get_bash()->env);
	init_signal(0);
	clean_up(line,token_lst);
}
