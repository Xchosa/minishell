/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:54:10 by poverbec          #+#    #+#             */
/*   Updated: 2025/05/27 17:35:39 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_tp.h"
#include "parser.h"

// include this in heredoc 
// signal(SIGINT,SIG_DFL) // in child process heredoc, if control c 


// allowed functions:
// sigaction, sigemptyset, sigaddset, 

/// watch codeVault 
// signal 

/*
 struct sigaction {
                void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/



void parent_handler(int sig)
{
    if (sig == SIGINT)
	{
		get_exit_codes()->last_exit_code = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
		// ft_putstr_fd("EXIT: 3\n", STDOUT_FILENO);
	}
}

void child_handler(int sig)
{
	
    if(sig == SIGINT)
    {
        write(1, "\n",1);
		get_exit_codes()->last_exit_code = 130; // sleep and then ctrl + C
    }
	else if (sig == SIGQUIT)
	{
		// ft_putstr_fd("EXIT: 3\n", STDOUT_FILENO);
		// printf("do i reach it");
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		get_exit_codes()->last_exit_code = 131; // sleep and then ctrl + D
	}
	return ;
}

// child 1
// parent 0

// one signal bevor user/ readline / start from here 
// one before execution 

// turn of ^c

// keep all bits except ECHOCTL"
// &= ~ECHOCTL
void hide_ctrl_in_terminal(void)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);// fpr termial controll
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	// how typing in the terminal is displayed, 
	// thats why stdin

}

void setup_readline_signals(void)
{
	struct sigaction sa;

	hide_ctrl_in_terminal();
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = parent_handler;
	
	// ctrl + c
	sigaction(SIGINT, &sa, NULL);

	//ctrl + slash -> ignored
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void setup_execution_signals(void)
{
	struct sigaction sa;

	hide_ctrl_in_terminal();
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = child_handler;

	sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}



void init_signal(int is_child)
{
    struct sigaction sa;

	hide_ctrl_in_terminal();
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);// clear blocked signals
	//changes signal action (replaces signal() for better control
	if(is_child == 1)
	{
		sa.sa_handler = child_handler;
		sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = parent_handler;
		sigaction(SIGINT, &sa, NULL);
   		sa.sa_handler = SIG_IGN; // ignore ctrl backslash
		sigaction(SIGQUIT, &sa, NULL);
	}
	
}
