

#include "parser.h"
#include "minishell.h"


// if export is stands alone it returns token export only

// multiple variables not handeled export h=7 g=9 w="cat makefile"

t_token* tokeniser_for_export(t_token *token_lst, char *line)
{
	t_token *new_token;
	if (skip_whitespace_and_check_for_eof(&line) == false)
			return(token_lst);
	new_token = create_token_q_case_and_export(&line, token_lst);
	tokenadd_back(&token_lst, new_token);
	line = update_export_line(line);
	while(*line)
	{
        if (ft_strncmp( "\"", line, 1) == 0)
            break;
		new_token = create_token_export_output(line);
		tokenadd_back(&token_lst, new_token);
		line = update_export_output_line(line);
	}
    return (token_lst);
}


bool check_for_export(t_token *token_lst)
{
	if(ft_strncmp("export", token_lst->token, 6) == 0)
		return (true);
	return (false);
}

// export g="ls -al"
// $g
// now should print env of ls -al 
// es muss noch mal getokenised werden


//export h="echo test"
// $g

// druckt test 
// tokens echo und test 

// export m=echo test
// $m 

// druckt empty line 


