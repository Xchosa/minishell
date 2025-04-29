/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/29 15:15:02 by poverbec         ###   ########.fr       */
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



// t_bash *get_bash(void);

// typedef struct s_bash
// {
	
// } 

// laxxer ==> lexical analyser
typedef enum s_type
{
	TEXT, // 0
	PIPE, // 1
	Redirect_input, // 2 
	Redirect_output, // 
	Redirect_output_append_mode,// >>
	here_doc,// <<
	S_Quote,
	D_Quote, // 3 (like " ")
	
}	t_type;

// nach prios sortieren < > enum  

typedef struct s_token
{
	char 			*token;// **weil eigenes envp erweitert werden muss
	t_type 			token_type;
	struct s_token 	*next;
	
}	t_token;

// parser dann in in zwei dim array
// zuordnen was zusammen gehoert

// ls <infile -l >outfile -a
typedef struct s_cmd
{
	t_list		*args; // **weil eigenes envp erweitert werden muss // e.g. echo abc cyz
	t_list 		*redirs; /// e.g. outfile.txt // auf void pointer von t_list
	struct s_cmd 	*next;
	
}	t_cmd;

// libft_struct
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_list;


typedef enum s_redirtype
{
	IN,
	OUT,
	APPEND,
	skip,
}	t_redirtype;

typedef struct s_redirs
{
	t_redirtype *Redirtype;
	char 		*file;
} t_redirs;


// 

// get input 
void		interactive_shell_tty(int argc, char **argv, char **envp, char *line);
void		non_interactive_shell(int argc, char **argv, char **envp, char *line);

// lexer
bool		lexer(char *line);
int			count_up_strings(char *line);
bool		wrong_use_pipe_and_redirection(char *line);
bool		check_for_correct_double_divider(char *line);
bool    	check_for_correct_single_divider(char *line);


// tokeniser
void 		skip_whitespace(char **line);
bool		skip_whitespace_and_eof(char **line);
bool		find_divider_until_whitespace_or_eof(char c);
bool		char_is_alpha_nbr_and_no_whitespace(char c);

t_token 	*tokeniser (char *line);
char		*get_token(char *content);
t_type		get_token_type(char *content);
t_token		*tokenlast(t_token *lst);
void		tokenadd_back(t_token **lst, t_token *new_token);

t_token		*create_token(char *content);
t_token		*d_quote_case(char **line);
t_token		*s_quote_case(char **line);
t_token		*create_token_with_quote_case(char **line);
t_token		*tokenlstnew(char	*content);
bool		check_for_divider_with_space(char c);
bool		check_for_divider_without_space(char c);
char		*update_line(char *line);
char		*update_line_unitl_d_quotes(char *line);
char		*update_line_unitl_s_quotes(char *line);
char 		*ft_charjoin(char const *dst, char const src_char);

void		iter_tokenlst(t_token *lst, void (*f)(t_token *));
void		print_tokenlst(t_token *data);

//here_doc
void		check_here_doc_and_take_exit_word(t_token *token_lst);
char		*cpy_str_space_deli(const char *src);
size_t		strlen_until_space(const char *s);
bool		not_single_divider(char c);
bool		pipe_or_simec(char c);


#endif