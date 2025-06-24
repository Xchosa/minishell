#ifndef EXECUTER_H
# define EXECUTER_H


# include "minishell.h"
# include <sys/wait.h>
# include <parser.h>

	// typedef struct s_exit_codes
	// {	
	// 	int last_exit_code; // update after every runexit
		
	// } t_exit_codes;

	// typedef struct s_bash
	// {
	// 	char **env;
		
	// } t_bash;

	// t_exit_codes	*get_exit_codes(void);
	// t_bash		*get_bash(void);

void	ft_echo(t_cmd_node *cmd_node, char **envp);
void	ft_pwd(char **envp);
void	ft_env(char **envp);
void	ft_cd(t_cmd_node *cmd_node, char **envp);
int		ft_isnum(char *s);
void	ft_exit(t_cmd_node *cmd_node);
void	ft_execute(t_cmd_list *cmd_list, char **envp);
void	ft_execute_node(
	t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp);
void	ft_execute_command(t_cmd_node *cmd_node, char **envp);
void	ft_execute_builtin(t_cmd_node *cmd_node, char **envp);
void	ft_open_pipes(int fd[][2], t_cmd_list *cmd_list);
void	ft_first_node(int fd[][2]);
void	ft_middle_node(int fd[][2], t_cmd_list *cmd_list, t_cmd_node *cmd_node);
void	ft_last_node(int fd [][2], t_cmd_list *cmd_list);
void	ft_close_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2]);
void	ft_manage_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2]);
void	ft_free_array2(char **array);
char	*ft_give_pointer_to_path(char **envp);
char	*ft_getpath(char *command, char **envp);
void	ft_manage_infile(char *infile, int fd[][2]);
void	ft_manage_outfile(char *outfile, int fd[][2]);
void	ft_manage_append(char *appendfile, int fd[][2]);
void	ft_manage_heredoc(char *delimiter, int fd[][2]);
void	ft_manage_redirections(t_cmd_node *cmd_node, int fd[][2]);
int		ft_get_index(int i, char **envp);
void	ft_export_print(char **envp);
void	ft_export_variable(char *cmd_var, char **envp);
void	ft_export(t_cmd_node *cmd_node, char **envp);
void	ft_unset_var(char **envp, int j);
void	ft_unset(t_cmd_node *cmd_node,char **envp);


//heredoc
bool	check_for_interactive_shell(void);
bool 	execute_here_doc(char *filename, int here_doc_fd);
int 	find_here_doc_file_node(t_file_node **file_node);
int		save_here_doc_in_tmp(t_file_node **file_node);
void	save_heredoc_files(t_cmd_node **cmd_node);

void	execute_loop(t_cmd_list **cmd_list);
void	ex_redirection(t_cmd_list **cur_cmd_node);
bool	handle_single_cmd_node(t_cmd_node **cur_cmd_node);

//# include "parser.h"


#endif