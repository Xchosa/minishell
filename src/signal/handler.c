
#include "signal.h"

// allowed functions
// signal,
// sigaction, sigemptyset, sigaddset, 
// getcwd, chdir, stat, lstat, fstat,


// Key	    Signal/Effect	    Default Behavior	    How to Handle in C
// Ctrl+C	SIGINT	            Interrupt/Terminate	    Use signal(SIGINT, handler)
// Ctrl+\	SIGQUIT	            Quit/Core Dump	        Use signal(SIGQUIT, handler)
// Ctrl+D	EOF(not a signal)	End of input (stdin)	Check for EOF in input functions
// EOF	    Value	             End file/stream	     Check for EOF in input functions



// Ctrl + C
// closes the STDIN Pipe ->flushes the current input 
// 2nd time program uses this garabe input
// static void handle_sigint(int sig) 
// {
//     printf("Caught SIGINT (Ctrl+C). Cleaning up...\n");
//     // free(line);
//     // free(token_lst);
//     exit(0);
// }

// Ctrl + 
// Meaning: Sends the SIGQUIT signal to the process.
// pressing Ctrl+\ will invoke your handler 
// instead of terminating the program
// static void handle_sigquit(int sig)
// {
//     printf("Caught SIGQUIT (Ctrl+\\).\n");
// }


// Ctrl+D signals the end-of-file (EOF) condition on the 
// terminal when input is being read in canonical mode.

// fgets()
// scanf()
// returns EOF -> -1 
//How to handle: Check the return value of 
// input functions for EOF.

/*
Fields within termios:
c_iflag: Input flags, controlling how input data is processed. 
c_oflag: Output flags, controlling how output data is sent. 
c_cflag: Control flags, configuring the terminal hardware. 
c_lflag: Local flags, affecting local terminal operations. 
c_cc: An array of special control characters (e.g., INTR, QUIT, ERASE). 

Functions for Terminal Control:
tcgetattr(fd, termios_p): Retrieves the current terminal attributes for a file descriptor 
fd and stores them in the termios structure pointed to by termios_p. 

tcsetattr(fd, optional_actions, termios_p): Sets the terminal attributes for a file descriptor
 fd based on the termios structure pointed to by termios_p. The optional_actions parameter
  specifies how the changes are applied (e.g., immediately, after output drains). 
  
tcdrain(fd): Waits for all output to be transmitted to the terminal. 
tcflush(fd, queue_selector): Flushes input or output data from the terminal queue. 
tcflow(fd, action): Controls flow control (e.g., suspending or restarting output). 
tcsendbreak(fd, duration): Sends a break signal to the terminal. 

*/


// approach with a extern volatile global variable
// volatile sig_atomic_t g_in_readline = 0;

// /*
//  struct sigaction {
//                 void     (*sa_handler)(int);
//                void     (*sa_sigaction)(int, siginfo_t *, void *);
//                sigset_t   sa_mask;
//                int        sa_flags;
//                void     (*sa_restorer)(void);
//            };
// */

// // include this in heredoc 
// // signal(SIGINT,SIG_DFL) // in child process heredoc, if control c 

// void signal_heredoc(void)
// {
// 	// (void)
// 	// heredoc is a child process where signals needs to be set
// 	//seperately 
// }



// void parent_handler(int sig)
// {
//     if (sig == SIGINT)
// 	{
// 		get_exit_codes()->last_exit_code = 1;
// 		if(g_in_readline != 0) // in readline mode then only print new line
// 		{
// 			write(STDOUT_FILENO, "\n", 1);
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 			rl_redisplay();
// 		}
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		get_exit_codes()->last_exit_code = ec_sucess;
// 	}
// }

// void child_handler(int sig)
// {
	
//     if(sig == SIGINT)
//     {
//         write(1, "\n",1);
// 		get_exit_codes()->last_exit_code = 130; // sleep and then ctrl + C
// 		exit(130);
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		write(STDOUT_FILENO, "Quit: 3\n", 8);
// 		get_exit_codes()->last_exit_code = 131; // sleep and then ctrl + D
// 	}
// 	return ;
// }


// void hide_ctrl_in_terminal(void)
// {
// 	struct termios term;
	
// 	tcgetattr(STDIN_FILENO, &term);// fpr termial controll
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
// }

// void setup_readline_signals(void)
// {
// 	struct sigaction sa;

// 	hide_ctrl_in_terminal();
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = parent_handler;
	
// 	// ctrl + c
// 	sigaction(SIGINT, &sa, NULL);

// 	//ctrl + slash -> ignored
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	rl_catch_signals = 0;
// 	// Tell readline not to install its own handlers
// }




// void init_signal(int is_child)
// {
//     struct sigaction sa;

// 	hide_ctrl_in_terminal();
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);// clear blocked signals
// 	//changes signal action (replaces signal() for better control
// 	if(is_child == 1)
// 		sa.sa_handler = child_handler;
// 	else
// 		sa.sa_handler = parent_handler;
// 	sigaction(SIGINT, &sa, NULL);
//    	sa.sa_handler = SIG_IGN; // ignore ctrl backslash
// 	sigaction(SIGQUIT, &sa, NULL);
// 	// sigaction(SIGTERM, &sa, NULL);
// 	// make sure readline doesn't interfere
// 	rl_catch_signals = 0;
// }





/// main
// static char* read_terminal(void)
// {
// 	char *line;
// 	// setup_readline_signals();
// 	tcflush(STDIN_FILENO, TCIFLUSH);

// 	g_in_readline = 1;
// 	setup_readline_signals();
// 	line = readline("minishell:$ ");
// 	g_in_readline = 0;
// 	if (line && *line)
//         add_history(line);
// 	if (line == NULL) // Handle EOF (Ctrl+D)
// 		{
//             printf("exit\n");
//             exit(get_exit_codes()->last_exit_code); /// clean everything   
//         }
// 	return(line);
// }

// void	interactive_shell_tty(int argc, char **argv, char **envp, char *line)
// {
// 	(void)argc;
// 	(void)envp;
// 	(void)argv;
// 	t_token *token_lst;
// 	t_exit_codes *exit_code;
// 	t_cmd_list *cmd_lst;
// 	(void)exit_code;
	
// 	// try to put in read_terminal
// 	t_bash *bash;
// 	while(1)
// 	{
// 		line = read_terminal();
// 		bash = get_bash();
// 		(void)bash;
// 		if (lexer(line) == false)
// 		{
// 			get_exit_codes()->last_exit_code = syntax_failure;
// 			print_error_message(line);
// 			free(line);
// 			continue;
// 		}
// 		token_lst = tokeniser(line);
// 		if (!token_lst)
// 		{
// 			free(line);
//             continue;
// 		}
// 		iter_tokenlst(token_lst, &print_tokenlst);
// 		extend_saved_export_var(token_lst);
		
// 		printf("\n append token string in export \n\n");
// 		append_export_str(&token_lst);
// 		iter_tokenlst(token_lst, &print_tokenlst);
// 		if (lexer_token(token_lst) == false)
//     	{
// 			print_error_message(line);
// 			free(line);
// 			free(token_lst);
// 			continue;
//     	}
// 		cmd_lst = init_cmd_list(&token_lst);
// 		printf("\n cmd_list works:\n\n");
// 		iter_cmd_lst(cmd_lst, &print_cmd_lst);

// 		printf("Thilos problem:\n");
// 		g_in_readline = 0;
// 		init_signal(0);
// 		ft_execute(cmd_lst, get_bash()->env);
// 	}
// 	if (token_lst)
//         free_token(&token_lst);
// 	if (!line)
// 		free(line);
// }