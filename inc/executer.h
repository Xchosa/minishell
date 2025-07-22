#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include <sys/wait.h>
# include <parser.h>

void	ft_echo(t_cmd_node *cmd_node);
void	ft_env(char **envp);
void	ft_cd(t_cmd_node *cmd_node, char **envp);
int		ft_isnum(char *s);
void	ft_exit(t_cmd_list *cmd_list, t_cmd_node *cmd_node);
void	ft_execute(t_cmd_list *cmd_list, char **envp);
void	ft_execute_command(t_cmd_node *cmd_node, char **envp);
void	ft_execute_builtin(t_cmd_list *cmd_list, t_cmd_node *cmd_node, char **envp);
bool	ft_open_pipes(int fd[][2], t_cmd_list *cmd_list);
bool	ft_first_node(int fd[][2]);
bool	ft_middle_node(int fd[][2], t_cmd_list *cmd_list, t_cmd_node *cmd_node);
bool	ft_last_node(int fd [][2], t_cmd_list *cmd_list);
void	ft_close_pipes(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2]);
void	close_pipe_and_free_fd(int (*fd)[2], int count, int size);

bool	ft_manage_pipes(
			t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2]);
char	*ft_give_pointer_to_path(char **envp);
char	*ft_getpath(char *command, char **envp);
bool	ft_manage_infile(char *infile);
bool	ft_manage_outfile(char *outfile);
bool	ft_manage_append(char *appendfile);
bool	ft_manage_redirections_multi(t_file_list *file_list);
void	manage_single_cmd_node(t_cmd_list *cmd_list, t_cmd_node *cmd_node, char **envp);
void	ft_execution_loop(t_cmd_list *cmd_list, char **envp, int (*fd)[2]);
bool	create_pipes(int (**fd)[2], t_cmd_list *cmd_list);
//bool	there_is_old_pwd(char **envp);
bool	there_is_env_var(char **envp, char *env_var);
char	**ft_add_relative_path(t_cmd_node *cmd_node, char **envp);
char	**ft_add_parent(char **envp);


bool	ft_manage_heredoc(char *tmp_filename);

int		ft_get_index(int i, char **envp);
bool	ft_check_valid_identifier(char *var);
void	ft_export_print(char **envp);
char	**ft_export_variable(char *cmd_var, char **envp);
void	ft_export(t_cmd_node *cmd_node, char **envp);
char	**ft_unset_var_by_index(char **envp, int j);
char	**ft_unset_var_by_name(char **envp, char *env_var);
void	ft_unset(t_cmd_node *cmd_node, char **envp);
void	ft_update_env_cd(t_cmd_node *cmd_node, char **envp);
void	ft_pwd(char **envp);
char	**ft_add_pwd(char *pwd, char **envp);
char	**ft_add_old_pwd(char **envp);
char	**ft_add_absolute_path(t_cmd_node *cmd_node, char **envp);
char	**ft_delete_old_pwd(char **envp);
void	ft_minishell_nested(char **envp);
void	ft_increase_shlvl(char **envp);
int		ft_ask_shlvl(char **envp);
char	*get_home_path(char **envp);
char	*ft_execute_local(char *command, char **envp);
char	*get_command_pointer(char *command, char **envp);

//heredoc
bool	check_for_interactive_shell(void);
bool	execute_here_doc(char *filename, int here_doc_fd);
int		find_here_doc_file_node(t_file_node **file_node);
int		save_here_doc_in_tmp(t_file_node **file_node);
void	save_heredoc_files(t_cmd_node **cmd_node);

void	reset_redir(int *backupStdin, int *backupStdout);
// void	set_up_backup_Stdout_Stdin(int *backupStdin, int *backupStdout);
void	execution_node(t_cmd_list *cmd_list,
			t_cmd_node *cmd_node, int fd[][2], char **envp);

#endif