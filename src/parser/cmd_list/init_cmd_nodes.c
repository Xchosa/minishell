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
	cmd_list->size = 0;

	return(cmd_list);
}

t_file_list *file_list_to_NULL(void)
{
	t_file_list *file_list;
    file_list = malloc(sizeof(t_file_list));
	if (!file_list)
		return (NULL);
    file_list->head = NULL;
    file_list->tail = NULL;
    file_list->size = 0;
    return  (file_list);
}



t_cmd_list	*init_cmd_list(t_token *token_list)
{
	t_cmd_list *cmd_list;
    t_file_list *file_list;
	t_token		*current_token;
	
	cmd_list = cmd_list_to_NULL();
    file_list = file_list_to_NULL();
	
	current_token = token_list;
	while(current_token->next)
	{
		process_token(current_token, cmd_list);
	
	current_token = current_token->next;
	}
    (void)file_list;
	return(cmd_list);
}