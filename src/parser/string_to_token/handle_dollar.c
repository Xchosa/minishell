
#include "parser.h"



t_token	*call_exit_token(char **line)
{
	t_token *new_token;
	(void)line;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token =ft_strdup("$?");
	new_token->token_type = CALL_EXIT;
	return (new_token);
}


t_token	*call_saved_export_var(char **line)
{
	int i;
	char *tmp_token;
	t_token *new_token;

	i = 0;
	new_token = malloc (sizeof(t_token));
	if(!new_token)
	return (NULL);
	new_token->token =ft_strdup("$");
	i++;
	while((*line)[i] != ' ' && (*line)[i] != '\0')
	{
		tmp_token = ft_charjoin( new_token->token, (*line)[i]);
		free(new_token->token);
        new_token->token = tmp_token;
		i++;
	}
	new_token->token_type = CALL_SAVED_VAR;
	return (new_token);
}