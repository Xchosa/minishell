

#include "parser.h"
#include "minishell.h"




void tokeniser_for_export(t_token *token_lst, char *line)
{
	t_token *new_token;
	if (skip_whitespace_and_eof(&line) == false)
			break;
	new_token = create_token_q_case_and_export(&line, token_lst);
	tokenadd_back(&token_lst, new_token);
	line = update_export_line(line);
	while(*line)
	{
        if (ft_strncmp( "\"", line, 1) == 0)
            break
		new_token = create_token_export_output(&line, token_lst);
		tokenadd_back(&token_lst, new_token);
		line = update_export_output_line(line;)
	}
    retun(token_lst)
}


bool handle_export_and_tokenise(t_token *token_lst,char *line)
{
	if(ft_strncmp("export", token_lst->token, 6) == 0)
	{
		tokeniser_for_export(token_lst, line);
		return (false);
	}
	return (true);
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


