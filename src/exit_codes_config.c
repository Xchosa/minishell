


#include "parser.h"
#include "minishell.h"



t_exit_codes	*get_exit_codes(void)
{
	static t_exit_codes	exit_code;

	return (&exit_code);
}

bool	init_exit_codes(int argc)
{
	t_exit_codes *exit_code;
	
	exit_code = get_exit_codes();
	if (argc == 1)
	{
		exit_code->last_exit_code = ec_sucess;
	}
	return (true);
}

bool print_error_message(char *line)
{
	int error;
	bool exit_minishell;
	exit_minishell = true;
	error = get_exit_codes()->last_exit_code;
	if (error == invalid_identifier)
		(printf("minishell: '%s': not a valid identifier \n", line));
	if (error == syntax_failure)
		(printf("minishell: '%s': syntax failure \n", line));
	if (error == cmd_not_found)
		(printf("minishell: '%s': command not found \n", line));
	if (error == syntax_error_token)
		(printf("minishell: syntax error near unexpected token '%s' \n", line));
	if (error == ec_sucess)
		return(exit_minishell = false);
	return(exit_minishell);
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
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		print_error_message(line);
		free(line);
		return(false);
    }
	return(true);
}
\
	
// $? wird als BUILTIN deklariert