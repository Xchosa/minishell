/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/24 16:19:19 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
#include <dirent.h>



#define syntax_failure 258
#define syntax_error_token 2
#define ec_sucess 0
#define ec_abort_z 146
// #define ec_failure 127
#define invalid_identifier 1
// control c -> 1
#define stopped 148
#define cmd_not_found 127


// t_bash *get_bash(void);

typedef struct s_bash
{
	char **env;
	
} t_bash;


typedef struct s_exit_codes
{	
	int last_exit_code; // update after every runexit
	
} t_exit_codes;

t_exit_codes	*get_exit_codes(void);
bool			init_exit_codes(int argc);

typedef enum s_type
{
	TEXT = 0, // 0
	Redirect_input = 3, // 2 
	Redirect_output = 4, // 
	Append = 5,// >>
	here_doc = 6,// <<
	Tilde = 7,
	Mix_Export_var = 8, // ha$t
	// S_Quote = 7,
	// D_Quote = 8, // (like " ")
	EXPORT = 9, // export
	Export_var =10, // from export hallo="ls -l" -> 'hallo' = Export_var  | ls -l normal TEXT
	CALL_EXIT = 11, // $?
	CALL_SAVED_VAR = 12, // $hello   e.g -holds 'world' or holds nothing
	Error =13,// node invalid
	PIPE = 14, // 1

}	t_type;

// export  word=hello -> evp word
// unset word 
// export hello="echo test" world="echo test | outfile"
// 
// '$hello' '>' 'outfile'
// 

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

// t_bash functions
char		**cpychar_arr(char** src);
bool		init_bash(char **env, int argc);
t_bash		*get_bash(void);
void 		ft_print_array(char **src);

// get input 
void		interactive_shell_tty(int argc, char **argv, char **envp, char *line);
void		non_interactive_shell(int argc, char **argv, char **envp, char *line);

//interrupt tty
bool check_lexer_and_free(char *line);
bool check_lexer_token_and_free(t_token *token, char *line);

// lexer
bool		lexer(char *line);
int			count_up_strings(char *line);
bool		wrong_use_pipe_and_redirection(char *line);
bool		check_for_correct_double_divider(char *line);
bool    	check_for_correct_single_divider(char *line);

// lexer tokens
bool		lexer_token(t_token *token_lst);
void		clean_up(char *line, t_token *token);
bool		tokeniser_successful(t_token *token_lst, char *line);

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
t_token 	*create_first_token(char **line);
t_token		*d_quote_case(char **line);
t_token		*s_quote_case(char **line);
t_token		*call_exit_token(char **line);
t_token		*call_saved_export_var(char **line);
t_token 	*create_token_with_quote_case(char **line, t_token *token);
t_token		*tokenlstnew(char	*content);
bool		check_for_divider_with_space(char c);
bool		check_for_divider_without_space(char c);
void 		free_token(t_token **token_list);

//update line
char		*update_line(char *line, t_token *token);
char 		*handle_special_characters(char *line);
char 		*handle_regular_token(char *line);
char		*update_line_unitl_d_quotes(char *line);
char		*update_line_unitl_s_quotes(char *line);
char		*update_line_until_space(char *line);
void		iter_tokenlst(t_token *lst, void (*f)(t_token *));
void		print_tokenlst(t_token *data);

//here_doc
void		check_here_doc_and_take_exit_word(t_token *token_lst);
char		*cpy_str_space_deli(const char *src);
bool		not_single_divider(char c);
bool		pipe_or_simec(char c);
int 		special_char_no_divider(char c);
int			special_char_no_divider_no_eq(char c);

void		delete_token(t_token *delete_token);

//	get export saved variables
t_token* 	extend_saved_export_var(t_token **token_lst);
char**		extend_env_with_str(char** src, char *token);
char* 		get_var_from_env(char **src, char *token_no_dollar);
char*		get_home_directory(char **src);
char*		extract_var_value(char *env_str, int start_pos);
void 		reset_token_get_var_from_env(t_token **token_lst, char **src);
void		reset_token_get_home_directory(t_token **token_lst, char **src);
// export tokenise 
t_token*	equal_case(char **line);
t_token*	split_token_in_sub_token(t_token *current_token, t_token *chain);
t_token*	create_token_splited(char *content);
char*		get_token_equal_as_div(char *content);
t_token*	create_token_equal_as_div(char *content);
void		handle_export(t_token *token_lst);

char*		get_export_token(char *content);
char*		update_export_line(char *line);
t_token*	create_export_token(char *content);
t_token*	create_token_q_case_and_export(char **line, t_token *token_lst);
bool		d_quote_case_no_div(char *line);
bool		split_needed(t_token **t_lst);
void 		append_export_str(t_token **token_lst);
bool		multiple_tokens(char *line);
char 		*handle_mulit_token(char *line);
char 		*skip_divider_without_space(char *line);
void 		tokenise_muliple_tok_from_env(t_token **token_lst, t_token *prev_token);
// cmd_list

//print cmd_lst
void	print_cmd_lst(t_cmd_node *cmd_nodes);
void	iter_cmd_lst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*));

t_cmd_list*		init_cmd_list(t_token **token_list);
t_cmd_list*		cmd_list_to_NULL(void);
t_file_list*	file_list_to_NULL(void);

t_cmd_node*		process_token(t_token **curr_token);
void 			process_token_type_Text(t_token **curr_token,t_cmd_node *cmd_node);
void 			append_token_char(t_cmd_node *cmd_node, t_token *curr_token);
char 			**cpy_token_char(char *token);
int				check_for_builtin(char *token_str);
int				choose_cmd_type(t_token *curr_token);
bool			redir_token(t_token **token_list);
void			process_redirect(t_token **curr_token, t_cmd_node *cmd_node);

// clean up
void	clean_token_lst(t_token *token_lst);
void	free_single_token(t_token **token);

//fill_file_list
t_file_node*	process_token_type_redir(t_token **curr_token);
t_file_node* 	create_redirect_input_file_node(t_token **curr_token);
t_file_node* 	create_redirect_output_file_node(t_token **curr_token);

// for new_libft
bool	ft_strcmp(const char *s1, const char *s2);
char	**ft_cpy_array_str(char **arrays);
char 	*ft_charjoin(char const *dst, char const src_char);
void 	ft_free_array(char **arrays);





#endif
