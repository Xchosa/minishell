
#include "parser.h"
#include "minishell.h"


t_token* process_token_type_Text(t_token *curr_token,t_cmd_node *cmd_node)
{
	while(curr_token && curr_token->token_type == TEXT)
	{
		if(cmd_node->cmd_type == 0)
		{
			cmd_node->cmd_type = choose_cmd_type(curr_token);
			cmd_node->cmd = cpy_token_char(curr_token->token);
		}
		else
		{
			append_token_char(cmd_node, curr_token);
		}
	curr_token = curr_token->next;
	}
	return (curr_token);
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

t_cmd_node* process_token(t_token *token_lst)
{
	t_cmd_node 	*cmd_node;

	t_file_list *file_list;
	file_list = file_list_to_NULL();
	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	
	// 	if(curr_token ->token_type == PIPE)
			// 
	while(token_lst && token_lst->next)
	{
		// process_token_type_export(curr_token, cmd_node)?
		token_lst=process_token_type_Text(token_lst,cmd_node);
		// generall function for red output/input append her_doc 
		

		// ganzer block der immer nur die curr_node zuruck gibt. 
		// man arbeitet ja die ganze zeit mit der selben cmd_node
		// new_token = process_token_type_redir

		if(file_list->head == NULL)
			{
				file_list->head = process_token_type_redir(token_lst);
				file_list->size +=1;
			}
		else
		{
			file_list->tail = process_token_type_redir(token_lst);
			file_list->tail = file_list->tail->next;
			file_list->size +=1;
			
		}
		
		// process_token_type_export_var();
		// process_token_call_exit;
		// if(curr_token ->token_type == PIPE)
		// 		break;
	}
	return(cmd_node);
}

