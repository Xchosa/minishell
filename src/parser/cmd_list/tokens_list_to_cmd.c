
#include "parser.h"
#include "minishell.h"





void process_token(t_token *current_token, t_cmd_list *cmd_list)
{
	//t_cmd_list	*tmp_list;
	t_cmd_node 	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return ;

	int len_char_array;
	len_char_array = 0;
	// current token hoch gecounted bis zur pipe oder ende
	while(current_token->next)
	{
		while(current_token->token_type == TEXT)
		{
			len_char_array++;
			cmd_node->cmd_type = choose_cmd_type(current_token);
		}
		if(current_token ->token_type == PIPE)
			break;
	}
	if(cmd_list->head == NULL)
		cmd_list->head = cmd_node;
	else
		cmd_list->tail->next = cmd_node;
	
	// in tmp_cmd_node alles rein und dann auf tail wenn head nicht null ist
	// 
	// if cmd typ ist 0 dann - in die funtion sonst skippen)
	// 	tmp_cmd_node->cmd_type = choose_cm

}
