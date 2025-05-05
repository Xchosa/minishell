

#include "parser.h"
#include "minishell.h"


t_cmd_list *cmd_list_to_NULL(void)
{
	t_cmd_list *cmd_list;
	cmd_list = malloc(sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = NULL;
}

void	iter_cmdlst(t_cmd_list *cmd_lst)
{
	if (cmd_lst == NULL)
		return ;
	while (cmd_lst != NULL)
	{
		f(cmd_lst);
		cmd_lst = cmd_lst->head->next;
	}
	return ;
}

char **init_buffer_10_arrays(void)
{
	char *buffer[10];
	int i;

	i = 0;
	buffer = malloc(10);
	while(i <= 10)
	{
		buffer[i]= '\0';
		i++;
	}
	return (buffer);
}

void process_token(t_token *current_token, t_cmd_list *cmd_list)
{
	
// echo test >outfile
// echo >outfile test ls -l <infile // test ls -l im outfile
// muss in dieselbe node
		// for each token_type own function


// irgendwie nicht vom head auf die node zugreiffen 
// sondern auf die current_cmd_list?
	if (current_token->token_type == TEXT)
	{
		init_buffer_10_arrays()
		cmd_list->head->cmd_type = EXECUTE;
		cmd_list->head->cmd = ft_strdup(current_token->token);
		cmd_list->head->file_list->head->redir_type = 0;
		if (!token_list->next);
	
	}
	if (current_token->token_type == PIPE)
	{
		cmd_list
	}
}
// im debugger nur get_next_line verhalten anschaun

// so lange txt token schreiben, wenn inile/ outfile uebersprinen und weiter
// bei anderen schliesen
char* fill_cmd(t_token current_token)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_read;
	static int 	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}



t_cmd_list	*init_cmd_list(t_token *token_list)
{
	t_cmd_list *cmd_list;
	t_token		*current_token;
	int i;
	
	
	cmd_list = cmd_list_to_NULL();
	i = 0;
	current_token = token_list;
	while(current_token->next)
	{
		process_token(&current_token, cmd_list);
	
	current_token = current_token->next;
	}

	return(cmd_list);
}


t_file_list *init_file_list(t_cmd_list *cmd_list)
{
	
}
