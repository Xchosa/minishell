

#include "parser.h"
#include "minishell.h"



// char **init_buffer_10_arrays(void)
// {
// 	char *buffer[10];
// 	int i;

// 	i = 0;
// 	*buffer = (char *)malloc(10 * (sizeof(char)));
// 	while(i <= 10)
// 	{
// 		buffer[i]= '\0';
// 		i++;
// 	}
// 	return (buffer);
// }

// void process_token(t_token *current_token, t_cmd_list *cmd_list)
// {
// 	char *tmp_line;
// 	int len_tmp_line;
// 	char **tmp_cmd;
// // echo test > outfile
// // echo >outfile test ls -l <infile // test ls -l im outfile
// // muss in dieselbe node
// 		// for each token_type own function


// // irgendwie nicht vom head auf die node zugreiffen 
// // sondern auf die current_cmd_list?
// 	if (current_token->token_type == TEXT)
// 	{
// 		cmd_list->head->cmd_type = EXECUTE;
// 		tmp_line = ft_strjoin(cmd_list->head->cmd, current_token->token);
// 		len_tmp_line= ft_strlen(cmd_list->head->cmd) + ft_strlen (tmp_line);
// 		free(cmd_list->head->cmd);
// 		ft_strlcpy(cmd_list->head->cmd, tmp_line, len_tmp_line);
// 		cmd_list->head->file_list->head->redir_type = 0;
// 		if (!current_token->next);
// 			return;
		 
// 	}
// 	else if (current_token->token_type == PIPE)
// 	{
// 		cmd_list->head->cmd_type = EXECUTE;
// 		cmd_list->head->cmd = ft_strdup(current_token->token);
// 	}
// 	else if ( current_token->token_type == Redirect_output)
// 	{
// 		cmd_list->head
// 	}
// }




// im debugger nur get_next_line verhalten anschaun

// so lange txt token schreiben, wenn inile/ outfile uebersprinen und weiter
// bei anderen schliesen
// char* fill_cmd(t_token current_token)
// {
// 	static char	buffer[BUFFER_SIZE];
// 	char		line[70000];
// 	static int	buffer_read;
// 	static int 	buffer_pos;
// 	int			i;

// 	i = 0;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (1)
// 	{
// 		if (buffer_pos >= buffer_read)
// 		{
// 			buffer_read = read(fd, buffer, BUFFER_SIZE);
// 			buffer_pos = 0;
// 			if (buffer_read <= 0)
// 				break ;
// 		}
// 		line[i++] = buffer[buffer_pos++];
// 		if (buffer[buffer_pos] == '\n')
// 			break ;
// 	}
// 	line[i] = '\0';
// 	if (i == 0)
// 		return (NULL);
// 	return (ft_strdup(line));
// }





