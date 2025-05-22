
#include "parser.h"
#include "minishell.h"

void free_token(t_token **token_list)
{
	t_token *next_token;
	t_token *delete_token;
	
	if (!token_list || !(*token_list))
        return;

	delete_token = *token_list;
	while(delete_token)
	{
		next_token = delete_token->next;
		free(delete_token->token);
		free(delete_token);
		delete_token = next_token;
	}
	*token_list= NULL;
}



static bool no_pipe(t_token **token_list)
{
	if(*token_list == NULL)
        return(false);

	if((*token_list)->token_type == PIPE)
	{
		(*token_list) = (*token_list)->next;
		return (false);
	}
	return (true);
}
static bool redir_token(t_token **token_list)
{
	int type;

	if(*token_list == NULL)
        return(false);
	type = (*token_list)->token_type;
	if (type == Redirect_input || type == Redirect_output 
        || type == Append || type == here_doc)
    	return (true);
	else
		return (false);
}

/*
	appends in cmd_node the cmd from each token
	changing or giving a cmd_type for the hole node until a pipe
	e.g. export h=world becommes type BUILTIN
	e.g. 
	if redirection a file list gets created
	looping and appending file_nodes to the head or tail of the file_list 
	until pipe
*/

t_cmd_node* process_token(t_token **token_lst)
{
	t_cmd_node 	*cmd_node;
	t_file_node *file_node;
	t_file_list *file_list;
	
	file_list = file_list_to_NULL();
	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->file_list = file_list;
	cmd_node->next = NULL;
	while((*token_lst)&& (*token_lst)->next)
	{
		process_token_type_Text(token_lst,cmd_node);
		if(no_pipe(token_lst) == false || redir_token(token_lst) == false)
			return(cmd_node);
		if(file_list->head == NULL)
			{
				file_list->head = process_token_type_redir(token_lst);
				file_node = file_list->head;
				file_list->tail = file_node;
			}
		else if((*token_lst)->token_type != PIPE && (*token_lst)->token_type != TEXT)
		{
			file_node->next = process_token_type_redir(token_lst);
			file_node = file_node->next;
			file_list->tail = file_node;
			file_list->size +=1;
		}
	}
	return(cmd_node);
}

