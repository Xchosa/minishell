

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


void process_token(t_token *current_token, t_cmd_list *cmd_list)
{
// echo test >outfile
		// for each token_type own function
	if (current_token->token_type == TEXT)
	{
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
