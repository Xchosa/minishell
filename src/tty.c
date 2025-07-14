/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:09:30 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/14 13:58:12 by poverbec         ###   ########.fr       */
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
*/

static char	*read_terminal(void)
{
	char	*line;
	char	*trimmed_line;

	init_signal(0);
	if (isatty(fileno(stdin)))
		line = readline("minishell:$ ");
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
            return (NULL);
		trimmed_line = ft_strtrim(line, "\n");
        free(line);
        line = trimmed_line;
	}
	if (line && *line)
		add_history(line);
	if (line == NULL)
	{
		printf("exit\n");
		// exit(get_exit_codes()->last_exit_code);
	}
	return (line);
}

// void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)

void	interactive_shell_tty(char *line)
{
	t_token		*token_lst;
	t_cmd_list	*cmd_lst;
	char		*original_line;

	cmd_lst = NULL;
	while (1)
	{
		line = read_terminal();
		if (line == NULL)
			break ;
		if (check_lexer_and_free(line) == false)
			continue ;
		original_line = line;
		token_lst = tokeniser(&line);
		if (tokeniser_successful(token_lst, original_line) == false)// frees line
			continue ;
		token_lst = extend_saved_export_var(&token_lst);
		append_export_str(&token_lst);
		if (lexer_token(token_lst) == false)
		{
			print_error_message(&token_lst, original_line);
			continue ;
		}
		cmd_lst = init_cmd_list(&token_lst, original_line);
		init_signal(1);
		ft_execute(cmd_lst, get_bash()->env);
		//  if (ft_execute(cmd_lst, get_bash()->env) == false)
        // {
        //     clean_cmd_lst(cmd_lst);
        //     break; // Exit the loop gracefully (wenn commando exit ist muss trotzdem gecleaned werden? )
        // }
		init_signal(0);
		reset_terminal_state();
		clean_cmd_lst(cmd_lst);
		cmd_lst = NULL;
	}
	clean_cmd_list_objects_tmp_files(cmd_lst);
	rl_clear_history();
}

// printf("\n append token string in export \n\n");
// iter_tokenlst(token_lst, &print_tokenlst);
// printf("\n cmd_list works:\n\n");
// iter_cmd_lst(cmd_lst, &print_cmd_lst)


void	non_interactive_shell(char *line)
{
	char		*original_line;
	t_token 	*token_lst;
	t_cmd_list 	*cmd_lst;

	line = get_next_line(STDIN_FILENO);
	if (check_lexer_and_free(line) == false)
		return ;
	original_line = line;
	token_lst = tokeniser(&line);
	if (tokeniser_successful(token_lst, original_line) == false)
		return ;
	token_lst = extend_saved_export_var(&token_lst);
	append_export_str(&token_lst);
	if (lexer_token(token_lst) == false)
	{
		print_error_message(&token_lst, original_line);
		return;
	}
	cmd_lst = init_cmd_list(&token_lst, original_line);
	init_signal(1);
	ft_execute(cmd_lst, get_bash()->env);
	init_signal(0);
	reset_terminal_state();
	clean_cmd_list_objects_tmp_files(cmd_lst);
	rl_clear_history();
}
