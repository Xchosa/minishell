



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
	
// 	// ctrl + c
// 	sigaction(SIGINT, &sa, NULL);

// 	//ctrl + slash -> ignored
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	rl_catch_signals = 0;
// 	// Tell readline not to install its own handlers
// }