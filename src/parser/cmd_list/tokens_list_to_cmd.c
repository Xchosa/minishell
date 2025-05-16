
#include "parser.h"
#include "minishell.h"




// t_file_node* process_token_types(t_token **token_lst)
// {
// 	t_file_node *file_node;
// 	file_node = malloc(sizeof(t_cmd_node));
// 	if (!file_node)
// 		return (NULL);
	
// 	file_node = process_token_type_Text(&token_lst,cmd_node);

// }







/*
	appends in cmd_node the cmd from each token
	changing or giving a cmd_type for the hole node until a pipe
	e.g. export h=world becommes type BUILTIN
	e.g. 
	if redirection a file list gets created
	looping and appending file_nodes to the head or tail of the file_list 
	until pipe
*/

static bool no_pipe(t_token **token_list)
{
	if((*token_list)->token_type == PIPE)
	{
		(*token_list) = (*token_list)->next;
		return (false);
	}
	return (true);
}
static bool no_redir(t_token **token_list)
{
	int type;

	type = (*token_list)->token_type;
	if (type == Redirect_input || type == Redirect_output 
        || type == Append || type == here_doc)
    	return (true);
	else
		return (false);
}


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
	while((*token_lst)&& (*token_lst)->next)
	{
		process_token_type_Text(token_lst,cmd_node);
		if(no_pipe(token_lst) == false || no_redir(token_lst) == false)
			return(cmd_node);
		if(file_list->head == NULL)
			{
				file_list->head = process_token_type_redir(token_lst);
				file_node = file_list->head;
				file_list->tail = file_node;
			}
		// if ((*token_lst) && (*token_lst)->token_type == PIPE)
		// {
		// 	(*token_lst) = (*token_lst)->next;
		// 	return (cmd_node);
		if((*token_lst)->token_type != PIPE && (*token_lst)->token_type != TEXT)
		{
			file_node->next = process_token_type_redir(token_lst);
			file_node = file_node->next;
			file_list->tail = file_node;
			file_list->size +=1;
		}
	}
	return(cmd_node);
}

