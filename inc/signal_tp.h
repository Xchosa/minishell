/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:26:29 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 13:56:25 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TP_H
# define SIGNAL_TP_H

# include "parser.h"
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

void	restore_terminal_behavoir(void);
void	init_signal(int child_or_parent);
void	child_handler(int sig);
void	parent_handler(int sig);
void	hide_ctrl_in_terminal(void);
void	reset_terminal_state(void);
void	reset_sig_handler_to_parent(void);

void	reset_sig_handler_to_child(void);
void	heredoc_signal(int is_child);
void	heredoc_handler(int sig);
bool	handle_signal_in_heredoc(char *filename, int here_doc_fd);

#endif