#ifndef SIGNAL_tp_H
# define SIGNAL_tp_H

# include "minishell.h"

# include <signal.h>
# include <fcntl.h>


void 	init_signal(int child_or_parent);
void	sig_int_handler_read(int sig);
void	setup_readline_signals(void);
void 	child_handler(int sig);
void	parent_handler(int sig);
#endif