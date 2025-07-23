/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:53:52 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 14:41:48 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"
#include <termios.h>


void	reset_sig_handler_to_parent(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	heredoc_signal(0);
}

void	reset_sig_handler_to_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	init_signal(1);
}

void	hide_ctrl_in_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	reset_terminal_state(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

	tcflush(STDIN_FILENO, TCIFLUSH);
}
// fflush(stdout);

// for heredoc // implementier heredoc funtionen und danach reset handler
//reset handlers and change signal for parent process
// bei ctrl D soll process beendien -> nur heredoc beenden rest 
// soll weiter gehen  -> korrekt

// cat <<1<<1<<1
// bei ctrl c soll aus allen heredocs raus
// ctrol D nur aus eins - funktioniert 

