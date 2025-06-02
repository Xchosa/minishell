/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/27 15:51:59 by poverbec         ###   ########.fr       */
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

	g_in_readline = 1;
	setup_readline_signals();
	tcflush(STDIN_FILENO, TCIFLUSH);
	line = readline("minishell:$ ");
	g_in_readline = 0;
	if (line && *line)
        add_history(line);
	if (line == NULL) // Handle EOF (Ctrl+D)
		{
            printf("exit\n");
            exit(get_exit_codes()->last_exit_code); /// clean everything   
        }
	return(line);
}

void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)
{
	(void)argc;
	(void)envp;
	(void)argv;
	t_token *token_lst;
	t_exit_codes *exit_code;
	t_cmd_list *cmd_lst;
	(void)exit_code;
	
	// try to put in read_terminal
	t_bash *bash;
	while(1)
	{
		reset_terminal_state();
		line = read_terminal();
		bash = get_bash();
		(void)bash;
		if (lexer(line) == false)
		{
			get_exit_codes()->last_exit_code = syntax_failure;
			print_error_message(line);
			free(line);
			continue;
		}
		token_lst = tokeniser(line);
		if (!token_lst)
		{
			free(line);
            continue;
		}
		iter_tokenlst(token_lst, &print_tokenlst);
		extend_saved_export_var(token_lst);
		
		printf("\n append token string in export \n\n");
		append_export_str(&token_lst);
		iter_tokenlst(token_lst, &print_tokenlst);
		if (lexer_token(token_lst) == false)
    	{
			print_error_message(line);
			free(line);
			free(token_lst);
			continue;
    	}
		cmd_lst = init_cmd_list(&token_lst);
		printf("\n cmd_list works:\n\n");
		iter_cmd_lst(cmd_lst, &print_cmd_lst);

		printf("Thilos problem:\n");
		g_in_readline = 0;
		init_signal(0);
		ft_execute(cmd_lst, get_bash()->env);
		g_in_readline = 1;
	}
	if (token_lst)
        free_token(&token_lst);
	if (!line)
		free(line);
}



void	non_interactive_shell(int argc, char **argv, char **envp ,char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	t_token 	*token_lst;
	t_bash 		*bash;
	t_exit_codes *exit_code;
	t_cmd_list 	*cmd_lst;

	(void)exit_code;
	(void)bash;
	bash = get_bash();
	printf("in the non interactive shell: \n");
	line = get_next_line(STDIN_FILENO);
	if(lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		printf("syntax Error: \n");
		printf("%s\n", line);
		return ;
	}
	token_lst = tokeniser(line);
	
	iter_tokenlst(token_lst, &print_tokenlst);
	extend_saved_export_var(token_lst);
	iter_tokenlst(token_lst, &print_tokenlst);
	handle_export(token_lst);
	printf("\n called form:\n\n");
	iter_tokenlst(token_lst, &print_tokenlst);
	printf("\ndo i come to cmd_list:\n\n");
	cmd_lst = init_cmd_list(&token_lst);
	iter_cmd_lst(cmd_lst, &print_cmd_lst);
	ft_execute(cmd_lst, get_bash()->env);
}