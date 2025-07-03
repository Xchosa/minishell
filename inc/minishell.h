
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

#define REDIRECT_INPUT 3 // <
#define REDIRECT_OUTPUT 4 // >
#define HERE_DOC 5 // <<
#define APPEND 6 // >>

#define BUILTIN 1 
#define EXECUTE 2

//List of redirection
typedef struct s_file_node
{
	int					redir_type;
	char				*filename;
	struct s_file_node	*next;
}	t_file_node;

//meta struct list 
typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	ssize_t		size;
}	t_file_list;	

// cmd_typ execute or builtin
typedef struct s_cmd_node
{
	int					cmd_type;
	char				**cmd;
	t_file_list 		*file_list;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	ssize_t		size;
}	t_cmd_list;

#endif