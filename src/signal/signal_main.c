
#include "signal.h"

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
    
}


// child 1
// parent 0
void child_handler(int sig)
{
    if(sig == SIGINT)
    {
        write(1, "\n",1)
        // update exit

    }
    // if child

    // if parent
}

// child 1
// parent 0
void init_signal(int child_or_parent)
{
    struct sigaction sa;           //changes signal action (replaces signal() for better control
    sa.sa_handler = handler;        // 
    sigemptyset(&sa.sa_mask)
    sigaddset(&sa.sa.mask,SIGQUIT); // block Siquit during handler
    sa.sa.flags = 0;
    
    if(child_or_parent)



}