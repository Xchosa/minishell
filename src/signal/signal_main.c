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
		(void)sig;
		get_exit_codes()->last_exit_code = 1;
	}
	else if (sig == SIGQUIT)
	{
		get_exit_codes()->last_exit_code = ec_sucess;
	}
}


// child 1
// parent 0
void child_handler(int sig)
{
	
    if(sig == SIGINT)
    {
        write(1, "\n",1);
		get_exit_codes()->last_exit_code = 130; // sleep and then ctrl + C
    }
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("EXIT: 3\n", 1);
		get_exit_codes()->last_exit_code = 131; // sleep and then ctrl + D
	}
	return ;
}

// child 1
// parent 0

// one signal bevor user/ readline / start from here 
// one before execution 

// turn of ^c
void turn_off_echo()
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// keeps any pending input in the buffer
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	// waits for all output to be transmitted first
}

void	sig_int_handler_read(int sig)
{
	(void)sig;
	get_exit_codes()->last_exit_code = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void setup_readline_signals(void)
{
	struct sigaction sa;
	// struct termios	term;

	// tcgetattr(STDIN_FILENO, &term);
	turn_off_echo();
	
	sa.sa_handler = sig_int_handler_read;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	// ctrl + c
	sigaction(SIGINT, &sa, NULL);

	//ctrl + slash -> it ignores 
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	
}


void init_signal(int child_or_parent)
{
    struct sigaction sa;
	struct sigaction sin;
	           //changes signal action (replaces signal() for better control
	if(child_or_parent == 0)
		sa.sa_handler = child_handler;  
	else
		sa.sa_handler = parent_handler;      // 
	sigemptyset(&sin.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	// sigadset(&sa.sa.mask,SIG_IGN);// control +C and  backslash

	// if child SIGQUIT is default
	// ignored in parent - runs on
	if(!child_or_parent)
   		sa.sa_handler = SIG_IGN;        // 
	sigaction(SIGQUIT, &sa, NULL);
    // sigemptyset(&sa.sa_mask)
    // sigaddset(&sa.sa.mask,SIGQUIT); // block Siquit during handler// only control + D 
    // sa.sa.flags = 0;

}



// restart from here 
// replace a new line , readline on new line, read the display again 
// in the termail again 


