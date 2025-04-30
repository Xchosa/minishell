

#include "parser.h"
#include "minishell.h"


t_cmd_list *cmd_list_to_NULL(void)
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	ssize_t		size;

	head = NULL;
	tail = NULL;
	size = NULL;
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


t_cmd_list	*init_cmd_list(t_token *token_list)
{
	t_cmd_list *cmd_list;
	t_token		*curr_token;
	int i;
	
	i = 0;
	cmd_list = cmd_list_to_NULL();
	
	while(token_list->next)
	{
		// each token_type own function
		if(token_list->token_type == TEXT)
		{
			cmd_list->head->cmd_type = 1;
			cmd_list->head->cmd = token_list->token;
			cmd_list->head->file_list
			if (!token_list->next)
			
		}
	
	cmd_list->head->next;
	}

	return(cmd_list);
}

