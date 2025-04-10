

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include "parser.h"


// List of redirection
typedef struct s_file_node
{
	char				*filname;
	// holing name of redirecting file
	int					redir_type;
	struct s_file_node	*next; 
}	t_file_node;


//meta struct list 
typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	ssize_t		size;
}	t_file_list;


typedef struct s_cmd_node
{
	char				**cmd; // option and args
	//t_type				type; // type of token
	struct s_cmd_node	*next;

}	t_cmd_node;

// meta struct command liste 
// poiter to first cmd and last command 
// sizse how often got forked
typedef struct s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	ssize_t		size;
}	t_cmd_list;

// singular linked list


// meta struct auf die immer zugegriffen wird 


#endif