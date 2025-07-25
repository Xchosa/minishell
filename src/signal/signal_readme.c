/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_readme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:25:05 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 10:40:00 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// in header declared as extern. value will be stored only one time
// not variables of normal headers where everything will be copyed and stored

/*
 struct sigaction {
                void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/

// include this in heredoc 
// signal(SIGINT,SIG_DFL) // in child process heredoc, if control c 

// child 1
// parent 0

// one signal bevor user/ readline / start from here 
// one before execution 

// turn of ^c

// keep all bits except ECHOCTL"
// &= ~ECHOCTL
// void setup_readline_signals(void)
// {
// 	struct sigaction sa;

// 	hide_ctrl_in_terminal();
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = parent_handler;
/*
Fields within termios:
c_iflag: Input flags, controlling how input data is processed. 
c_oflag: Output flags, controlling how output data is sent. 
c_cflag: Control flags, configuring the terminal hardware. 
c_lflag: Local flags, affecting local terminal operations. 
c_cc: An array of special control characters (e.g., INTR, QUIT, ERASE). 

Functions for Terminal Control:
tcgetattr(fd, termios_p): Retrieves the current terminal attributes
 for a file descriptor 
fd and stores them in the termios structure pointed to by termios_p. 

tcsetattr(fd, optional_actions, termios_p): Sets the terminal attributes 
for a file descriptor
 fd based on the termios structure pointed to by termios_p. 
 The optional_actions parameter
  specifies how the changes are applied (e.g., immediately,
  after output drains). 
  
tcdrain(fd): Waits for all output to be transmitted to the terminal. 
tcflush(fd, queue_selector): Flushes input or output data from the
 terminal queue. 
tcflow(fd, action): Controls flow control (e.g., suspending or
 restarting output). 
tcsendbreak(fd, duration): Sends a break signal to the terminal. 

*/