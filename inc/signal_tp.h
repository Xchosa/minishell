#ifndef SIGNAL_tp_H
# define SIGNAL_tp_H

// # include "minishell.h"
# include "parser.h"
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

extern volatile sig_atomic_t g_in_readline;

void 	init_signal(int child_or_parent);
void 	child_handler(int sig);
void	parent_handler(int sig);
void    hide_ctrl_in_terminal(void);
void    reset_terminal_state(void);
void    reset_sig_handler_to_parent(void);

void	reset_sig_handler_to_child(void);
void	heredoc_signal(int is_child);
void	heredoc_handler(int sig);

#endif