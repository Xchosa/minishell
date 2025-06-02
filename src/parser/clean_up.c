

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

bool tokeniser_successful(t_token *token_lst, char *line)
{
	if (!token_lst)
	{
		free(line);
		return (false);
	}	
	return(true);
}

bool check_lexer_token_and_free(t_token *token, char *line)
{
	if (lexer_token(token) == false)
	{
		print_error_message(line);
		free(line);
		free(token);
		return(false);
	}
	return(true);
}

bool check_lexer_and_free(char *line)
{
	if (line == NULL)
        return(false);
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		print_error_message(line);
		free(line);
		return(false);
    }
	return(true);
}
