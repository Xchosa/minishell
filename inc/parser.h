/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/15 13:57:26 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>

// t_config* get_config(void);

// typedef struct s_config
// {
// 	t_token **token_lst;
// 	// ...
// } t_config;

// laxxer ==> lexical analyser
typedef enum s_type
{
	TEXT, // 0
	PIPE, // 1
	Redirect_input, // 2
	Redirect_output, //
	Quote, // 3 (like " ")
}	t_type;



typedef struct s_token
{
	char 			**token;
	t_type 			token_type;
	struct s_token 	*next;
	
}	t_token;



// get input 
void		interactive_shell_tty(int argc, char **argv, char **envp, char *line);
void		non_interactive_shell(int argc, char **argv, char **envp, char *line);

// lexer
bool		lexer(char *line);
bool		wrong_use_pipe_and_redirection(char *line);
void		loop_until_space_or_operator(char **line);

// tokeniser
bool 		tokeniser (char *line);
char		*get_token(char *content);
t_type		get_token_type(char *content);
t_token		*tokenlast(t_token *lst);
void		tokenadd_back(t_token **lst, t_token *new_token);
t_token		*create_token(char *content);
t_token		*tokenlstnew(char	*content);

void		iter_tokenlst(t_token *lst, void (*f)(t_token *));
void		print_tokenlst(t_token *data);








#endif