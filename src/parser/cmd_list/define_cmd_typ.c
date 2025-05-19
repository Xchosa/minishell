#include "parser.h"
#include "minishell.h"


// what happens with test echo hallo
// lexer_before?


int check_for_builtin(char *token_str)
{
    if(ft_strncmp("echo" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("env" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("export" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("cd" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("pwd" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("unset" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("$?" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	if(ft_strncmp("exit" , token_str, ft_strlen(token_str)) == 0)
		return (BUILTIN);
	return 0;
}

int choose_cmd_type(t_token *curr_token)
{
    int cmd_type;

    cmd_type = 0;
	cmd_type = check_for_builtin(curr_token->token);
    if(cmd_type != 0)
        return(cmd_type);
    return(cmd_type = EXECUTE);
}