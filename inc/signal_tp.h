#ifndef SIGNAL_tp_H
# define SIGNAL_tp_H

// # include "minishell.h"
# include "parser.h"
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

extern volatile sig_atomic_t g_in_readline;

void 	init_signal(int child_or_parent);
void	sig_int_handler_read(int sig);
void	setup_readline_signals(void);
void 	child_handler(int sig);
void	parent_handler(int sig);
void    hide_ctrl_in_terminal(void);
void    reset_terminal_state(void);
void    setup_execution_signals(void);

void    setup_shell_signals(void);
void    setup_child_signals(void);
void    signal_heredoc(void);
#endif