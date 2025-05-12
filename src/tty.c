/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/06 15:45:20 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

// void	free_lst(t_token **token_lst, void (*del)(void *))
// {
// 	t_token_lst	*tmp
// 	f(!token_lst)
// 		return(Null)
// 	while(token_lst != NULL)
// 	{
// 		tmp = (*token_lst)-> next;
// 		del(*token_lst)-> char;
// 		free(*token_lst);
// 		token_lst = tmp;
// 	}
// 	*token_lst = NULL;
// }


void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	t_token *token_lst;
	while(1)
	{
		// command holen
		line = readline("Paul's coole bash:$ ");
		add_history(line);
		if(lexer(line) == false)
		{
			get_exit_codes()->last_exit_code = syntax_failure;
			printf("syntax Error: \n");
			printf("%s\n", line);
			return ;
		}
		token_lst = tokeniser(line);
		{
			// check_here_doc_and_take_exit_word(token_lst);
			iter_tokenlst(token_lst, &print_tokenlst);
		}
	}
	// free_lst(token_lst, del());

	
}

void	non_interactive_shell(int argc, char **argv, char **envp ,char *line)
{
	(void) argv;
	(void) argc;
	(void) envp;
	
	t_token *token_lst;
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
	{
		iter_tokenlst(token_lst, &print_tokenlst);
	}
}