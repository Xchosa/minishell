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


/*
process_token returns a cmd_node
which happens to be the head of the cmd_list 
or gets appended to the tail;

In the cmd_node is a pointer to the file_list if there happens
to be pipes or redirections. 
*/


t_cmd_list	*init_cmd_list(t_token **token_list)
{
	t_cmd_list *cmd_list;
	t_cmd_node 	*cmd_node;
	
	cmd_list = cmd_list_to_NULL();
	
	while((*token_list) && (*token_list)->next)
	{
		if(cmd_list->head == NULL)
		{
			cmd_list->head = process_token(token_list);
			cmd_node = cmd_list->head;
			cmd_list->tail = cmd_node;
			cmd_list->size +=1;
		}
		else
		{
			cmd_node->next = process_token(token_list);
			cmd_node = cmd_node->next;
			cmd_list->tail = cmd_node;
			cmd_list->size +=1;
		}
	}
	return(cmd_list);
}
