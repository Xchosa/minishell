


#include "parser.h"
#include "minishell.h"


// herdoc does not need to update history

void check_here_doc_and_take_exit_word(t_token *token_lst)
{
	char *her_doc_string;
	char *doc_line;
	int len_her_doc_string;

    while(token_lst != NULL)
	{
		if(token_lst->token_type == here_doc)
		{
			token_lst = token_lst->next;
			her_doc_string = ft_strdup(token_lst->token);//no space befor or after
			len_her_doc_string = ft_strlen(her_doc_string);
			while(1)
			{
				doc_line = readline("another heredoc> ");
				if(ft_strncmp(doc_line, her_doc_string, len_her_doc_string) == 0)
					break;
			}
		}
		token_lst = token_lst->next;
	}
}