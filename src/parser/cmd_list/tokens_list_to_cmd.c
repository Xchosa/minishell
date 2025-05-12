
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

// t_file_list *init_file_list(t_cmd_list *cmd_list)
// {
	
// }

int choose_cmd_type(char *token_str)
{
	if(ft_strncmp("echo" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("env" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	else
		return 0;
}

void process_token(t_token *current_token, t_cmd_list *cmd_list)
{
	//t_cmd_list *tmp_list;
	t_token *tmp_token;
	(void )tmp_token;
	//t_cmd_node tmp_cmd_node;
	(void )cmd_list;
	tmp_token = current_token;

	int len_char_array;
	len_char_array = 0;
	// current token hoch gecounted bis zur pipe oder ende
	while(current_token->next)
	{
		if(current_token->token_type == TEXT)
			len_char_array++;
		if(current_token ->token_type == PIPE)
			break;
		current_token = current_token->next;
	}
	
	// in tmp_cmd_node alles rein und dann auf tail wenn head nicht null ist
	// 
	// if cmd typ ist 0 dann - in die funtion sonst skippen)
	// 	tmp_cmd_node->cmd_type = choose_cm

}

t_cmd_list	*init_cmd_list(t_token *token_list)
{
	t_cmd_list *cmd_list;
	t_token		*current_token;
	
	cmd_list = cmd_list_to_NULL();
	
	current_token = token_list;
	while(current_token->next)
	{
		process_token(current_token, cmd_list);
	
	current_token = current_token->next;
	}

	return(cmd_list);
}