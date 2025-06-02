

#include "parser.h"



void clean_up(char *line, t_token *token_lst)
{
	if (token_lst)
        free_token(&token_lst);
	if (!line)
		free(line);
	// free(env)
	// free(cmdlist)
}