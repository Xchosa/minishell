/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 14:44:24 by poverbec         ###   ########.fr       */
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
# include <dirent.h>

# define SYNTAX_FAILURE 258
# define SYNTAX_ERROR_TOKEN 2
# define EC_SUCESS 0
# define EC_ABORT_Z 146
# define INVALID_IDENTIIER 1
# define CMD_NOT_FOUND 127 

typedef struct s_bash
{
	char		**env;
	char		*path;
	t_cmd_list	*cmd_garbage;
	char		*herdoc_filename;
}	t_bash;

typedef struct s_exit_codes
{
	int	last_exit_code;
}	t_exit_codes;

t_exit_codes	*get_exit_codes(void);
bool			init_exit_codes(int argc);

typedef enum s_type
{
	TEXT = 0,
	Redirect_input = 3,
	Redirect_output = 4,
	Append = 5,
	here_doc = 6,
	Tilde = 7,
	Mix_Export_var = 8,
	EXPORT = 9,
	Export_var =10,
	CALL_EXIT = 11,
	CALL_SAVED_VAR = 12,
	Error =13,
	PIPE = 14,
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			token_type;
	struct s_token	*next;
	struct s_token	*head;
}	t_token;

// t_bash functions
char			**cpychar_arr(char **src);
bool			init_bash(char **env, int argc);
t_bash			*get_bash(void);
void			ft_print_array(char **src);
void			set_heredoc_cmd_list(t_cmd_list *cmd_list);

// get input 
void			interactive_shell_tty(char *line);
void			non_interactive_shell(void);
bool			handle_line(char *line);

//interrupt tty
bool			check_lexer_and_free(char *line);
bool			check_lexer_token_and_free(t_token *token, char *line);

// lexer
bool			lexer(char *line);
int				count_up_strings(char *line);
bool			lexer_error_chars(char *line);
bool			wrong_use_pipe_and_redirection(char *line);
bool			check_for_correct_double_divider(char *line);
bool			check_for_correct_single_divider(char *line);
bool			check_syntax_heredoc(char *heredoc_del);

// lexer tokens
bool			lexer_token(t_token *token_lst, char *original_line);
bool			tokeniser_successful(t_token *token_lst, char *original_line);
void			print_error_message(t_token **token_lst, char *line);
void			print_lexer_error_message(char *line);
bool			final_lexer(t_token *token_lst, char *original_line);
bool			lexer_correct_export_var(t_token *token_lst,
					char *original_line);
bool			check_last_node_syntax(t_token *token_lst);
bool			check_correct_export_var(char *str);
bool			check_for_cmd(t_token *token);

// tokeniser
void			skip_whitespace(char **line);
bool			skip_whitespace_and_check_for_eof(char **line);
void			skip_quotes(char **line);
bool			skip_double_quotes(char **content);
bool			skip_d_quotes_and_following_quotes(char **line, int i);
bool			skip_s_quotes_and_following_qutes(char **line, int i);
void			skip_single_quotes(char **line);
bool			find_divider_until_whitespace_or_eof(char c);
bool			char_is_alpha_nbr_and_no_whitespace(char c);
int				process_content_to_token(char **line, t_token *token);

t_token			*validate_token_str(t_token **token);
t_token			*tokeniser(char **line);
char			*get_token(char **content);
t_type			get_token_type(char *content);
char			*tokenise_divider(char **content, char *new_token);
t_token			*tokenlast(t_token *lst);
bool			tokenadd_back(t_token **lst, t_token *new_token);
char			*add_char(char **content, char *tmp_token,
					char *new_token, int i);

void			set_last_node_null(t_token **lst);
t_token			*create_token(char **content);
t_token			*create_first_token(char **line);
t_token			*d_quote_case(char **line);
t_token			*s_quote_case(char **line);
t_token			*call_exit_token(char **line);
t_token			*call_saved_export_var(char **line);
t_token			*create_token_with_quote_case(char **line, t_token *token);
t_token			*tokenlstnew(char	**content);
bool			check_for_divider_with_space(char c);
bool			check_for_divider_without_space(char c);
void			free_token(t_token **token_list);
void			define_token_type(t_token *new_token);
bool			is_redirect(char *content);

//update line
void			iter_tokenlst(t_token *lst, void (*f)(t_token *));
void			print_tokenlst(t_token *data);

//here_doc
bool			not_single_divider(char c);
void			change_filename(char *new_tmp_file_name);

// extend_line
char			*extend_line(char **line);
char			*get_env_in_line( char **line);
char			*d_qoutes_swap_dollar_var_with_env_var(char *new_line,
					char *tmp_line, char **line);
char			*swap_dollar_var_with_env_var(char *new_line,
					char *tmp_line, char **line);
char			*add_single_char_to_line(char *new_line,
					char *tmp_line, char **line);
char			*add_s_quotes_str_to_line(char *new_line, char *tmp_line,
					char **line);
char			*swap_exit_code_in_line(char *new_line,
					char *tmp_line, char **line);
char			*extend_line_with_tilde(char *new_line,
					char *tmp_line, char **line);
char			*extend_line_with_env_str(char *new_line,
					char *tmp_line, char **line);
//	get export saved variables
char			*append_export_var(char *token_str, char **content);
char			*get_export_token_in_quotes(char **content);
char			*get_var_from_env(char **src, char *token_no_dollar);
char			*get_home_directory(char **src);
char			*extract_var_value(char *env_str, int start_pos);
void			reset_token_get_var_from_env(t_token **token_lst, char **src);
void			reset_token_get_home_directory(t_token **token_lst, char **src);
// export tokenise 
t_token			*equal_case(char **line);
t_token			*create_token_equal_as_div(char **content);

bool			d_quote_case_no_div(char *line);
// cmd_list

void			check_cmd_builtin(t_cmd_node **cmd_node);
int				correct_cmd_type(t_cmd_node **cmd_node);
void			process_token_type_text(t_token **curr_token,
					t_cmd_node *cmd_node);
//print cmd_lst
void			print_cmd_lst(t_cmd_node *cmd_nodes);
void			iter_cmd_lst(t_cmd_list *cmd_lst, void (*f)(t_cmd_node*));

t_cmd_list		*init_cmd_list(t_token **token_list, char *line);
t_cmd_node		*init_cmd_node_null(t_file_list *file_list);
t_cmd_list		*cmd_list_to_null(void);
t_file_list		*file_list_to_null(void);

t_cmd_node		*process_token(t_token **curr_token);
bool			process_s_q_content_to_token(char **line, t_token *token_node);
void			handle_special_cases(t_token **curr_token,
					t_cmd_node *cmd_node);
void			process_token_type_text(t_token **curr_token,
					t_cmd_node *cmd_node);
void			append_token_char(t_cmd_node *cmd_node, t_token *curr_token);
char			**cpy_token_char(char *token);
int				check_for_builtin(char *token_str);
int				choose_cmd_type(t_token *curr_token);
bool			redir_token(t_token **token_list);
void			process_redirect(t_token **curr_token, t_cmd_node *cmd_node);

// clean up
void			clean_test_minishell(t_cmd_list *cmd_list);
void			exit_cleanup(void);
void			clean_token_lst(t_token *token_lst);
void			exit_heredoc_clean(void);
void			clean_token_lst_and_line(t_token *token_lst, char *line);
void			free_single_token(t_token **token);
void			clean_token_lst_and_line(t_token *token_lst, char *line);
void			clean_cmd_lst(t_cmd_list *cmd_list);
void			clean_file_lst(t_file_list *file_list);
void			delete_tmp_files(const char *foldername);
void			clean_cmd_list_objects_tmp_files(t_cmd_list *cmd_list);
void			clean_exit_codes(void);
void			clean_bash_env(void);
char			*ft_strtolower(char *input);
void			clean_token_lst_and_readline(t_token *token_list, char *line);
void			free_before_heredoc(char *new_tmp_file_name, char *suffix,
					char *n_t_file_name_suf);

//fill_file_list
t_file_node		*process_token_type_redir(t_token **curr_token);
t_file_node		*create_redirect_input_file_node(t_token **curr_token);
t_file_node		*create_redirect_output_file_node(t_token **curr_token);

// for new_libft
//bool	ft_strcmp(const char *s1, const char *s2);
// char	**ft_cpy_array_str(char **arrays);
char			*ft_charjoin(char *dst, char src_char);
// void 	ft_free_array(char **arrays);

#endif
