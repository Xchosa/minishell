/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/21 15:43:11 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"
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
	t_bash *bash;

	line = readline("minishell:$ ");
	if (line && *line)
        add_history(line);
	bash = get_bash();
	(void)bash;
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
		line = read_terminal();
		if (!line) 
		{
            printf("\nexit\n");
            break;
        }
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
		free(line);
		if (!token_lst)
            continue;
		iter_tokenlst(token_lst, &print_tokenlst);
		if(extend_env(token_lst)== true)
		{
			printf("\nenv extended:\n");
			ft_print_array(bash->env);
			free_token(&token_lst);
			continue;
		}
		printf("\n$var from env:\n");
		extend_saved_export_var(token_lst);
		iter_tokenlst(token_lst, &print_tokenlst);
		
		handle_export(token_lst);
		printf("\n called form:\n\n");
		iter_tokenlst(token_lst, &print_tokenlst);
		printf("\ndo i come to _cmd_list:\n\n");

		cmd_lst = init_cmd_list(&token_lst);
		printf("\ndo i come to print_cmd_list:\n\n");
		iter_cmd_lst(cmd_lst, &print_cmd_lst);

		printf("Thilos problem:\n");
		ft_execute(cmd_lst, get_bash()->env);
	}
	if (token_lst)
        free_token(&token_lst);
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