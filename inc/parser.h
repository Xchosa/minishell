/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:21 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>


#define syntax_failure 258
#define ec_sucess 0
#define ec_abort_z 146
#define ec_failure 127
#define invalid_identifier 1


// t_bash *get_bash(void);

typedef struct s_bash
{
	char **env;
	
} t_bash;


char		**cpychar_arr(char** src);
bool		init_bash(char **env, int argc);
t_bash		*get_bash(void);
void 		ft_print_array(char **src);

typedef struct s_exit_codes
{	
	int last_exit_code; // update after every runexit
	
} t_exit_codes;

t_exit_codes	*get_exit_codes(void);
bool			init_exit_codes(int argc);

typedef enum s_type
{
	TEXT, // 0
	PIPE, // 1
	Redirect_input, // 2 
	Redirect_output, // 
	Redirect_output_append_mode,// >>
	here_doc,// <<
	S_Quote,
	D_Quote, // (like " ")
	EXPORT, // export dffdf="echo hello" <<here_doc // should work
	CALL_EXIT, // $?
	CALL_SAVED_VAR, // $hello   

}	t_type;

// nach prios sortieren < > enum  

typedef struct s_token
{
	char 			*token;// **weil eigenes envp erweitert werden muss
	t_type 			token_type;
	struct s_token 	*next;
	struct s_token	*head;
	
}	t_token;


// redir_type 
// infile <
// outfile >
// heredoc <<
// outfile append >>








// get input 
void		interactive_shell_tty(int argc, char **argv, char **envp, char *line);
void		non_interactive_shell(int argc, char **argv, char **envp, char *line);

// lexer
bool		lexer(char *line);
int			count_up_strings(char *line);
bool		wrong_use_pipe_and_redirection(char *line);
bool		check_for_correct_double_divider(char *line);
bool    	check_for_correct_single_divider(char *line);

bool    	lexer_valid_ident(char *line);
bool		d_quote_case_no_div(char *line);
bool		only_one_cmd(char *line);
bool 		export_case(char *line);


bool 		print_error_message(char *line);

// tokeniser
void 		skip_whitespace(char **line);
bool		skip_whitespace_and_check_for_eof(char **line);
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
t_token		*call_exit_token(char **line);
t_token		*call_saved_export_var(char **line);
t_token		*create_token_with_quote_case(char **line);
t_token		*tokenlstnew(char	*content);
bool		check_for_divider_with_space(char c);
bool		check_for_divider_without_space(char c);
char		*update_line(char *line);
char		*update_line_unitl_d_quotes(char *line);
char		*update_line_unitl_s_quotes(char *line);
char		*update_line_until_space(char *line);
char 		*ft_charjoin(char const *dst, char const src_char);

void		iter_tokenlst(t_token *lst, void (*f)(t_token *));
void		print_tokenlst(t_token *data);

//here_doc
void		check_here_doc_and_take_exit_word(t_token *token_lst);
char		*cpy_str_space_deli(const char *src);
size_t		strlen_until_space(const char *s);
bool		not_single_divider(char c);
bool		pipe_or_simec(char c);
int 		special_charcter_no_divider(char c);

// export tokenise 
t_token*	tokeniser_for_export(t_token *token_lst, char *line);
bool		check_for_export(t_token *token_lst);
bool		check_for_export_divider(char c);
char*		handle_dividers_in_export(char *content);
char*		get_token_export_output(char *content);
bool		check_divider_and_d_quotes_eof(char *line);
char*		update_export_output_line(char *line);
t_token*	create_token_export_output(char *line);
char*		get_export_token(char *content);
char*		update_export_line(char *line);
t_token*	create_export_token(char *content);
t_token*	create_token_q_case_and_export(char **line, t_token *token_lst);
bool		d_quote_case_no_div(char *line);

// cmd_list

//print cmd_lst
void	print_cmd_lst(t_cmd_node *cmd_nodes);
void	iter_cmdlst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*));

void	process_token(t_token *current_token, t_cmd_list *cmd_list);
#endif



// typedef struct s_cmd
// {
// 	t_list		*args; // **weil eigenes envp erweitert werden muss // e.g. echo abc cyz
// 	t_list 		*redirs; /// e.g. outfile.txt // auf void pointer von t_list
// 	struct s_cmd 	*next;
	
// }	t_cmd;

// // libft_struct
// // typedef struct s_list
// // {
// // 	void			*content;
// // 	struct s_list	*next;
// // }					t_list;


// typedef enum s_redirtype
// {
// 	IN,
// 	OUT,
// 	APPEND,
// 	skip,
// }	t_redirtype;

// typedef struct s_redirs
// {
// 	t_redirtype *Redirtype;
// 	char 		*file;
// } t_redirs;
