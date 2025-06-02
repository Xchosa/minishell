


#include "parser.h"
#include "minishell.h"


void check_here_doc_and_take_exit_word(t_token *token_lst)
{
	char *her_doc_string;
	char *doc_line;
	char *tmp_doc_line;
	int len_tmp_doc_line;

    while(token_lst != NULL)
	{
		if(token_lst->token_type == here_doc)
		{
			token_lst = token_lst->next;
			her_doc_string = ft_strdup(token_lst->token);//no space befor or after
			while(1)
			{
				doc_line = readline("another heredoc> ");
				//doc_line = "wow";
				tmp_doc_line = cpy_str_space_deli(doc_line);// nur spaces for dem word entfernen - 
				len_tmp_doc_line = ft_strlen(tmp_doc_line);
				if(ft_strncmp(tmp_doc_line, her_doc_string, len_tmp_doc_line) == 0)// len_her_doc_string- muss am anfang die strings entfert bekommen
				{
					free(tmp_doc_line);
					free(her_doc_string);
					break;
				}
				free(tmp_doc_line);
			}
		}
		token_lst = token_lst->next;
	}
}


char *cpy_str_space_deli(const char *src)
{
	char *her_doc_string;
	int count_len;
	int i;

	count_len = 0;
	i = 0;
	if (src == NULL)
		return (NULL);
	while((ft_strncmp(" ", &src[i], 1) == 0))
		i++;
	count_len = ft_strlen(src + i);
	her_doc_string = (char *)malloc((count_len + 1) * (sizeof(char)));
	// while (src[i] != '\0' && ft_strncmp(" ", &src[i], 1) != 0)
	while (src[i] != '\0')
	{
		her_doc_string[i] = src[i];
		i++;
	}
	her_doc_string[i] ='\0';
	return (her_doc_string);
}

