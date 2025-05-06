


#include "parser.h"
#include "minishell.h"

char* get_export_token(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	while (ft_strncmp("=", *content, 1) != 0)
	{
		// lexer fischt alle export 6h="echo test" heraus
		i++;
	}

}


t_token *create_export_token(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_export_token(content);
	new_token->token_type = EXPORT;// change
	new_token->next = NULL;
	return (new_token);
	// tokenadd_back(get_config()->token_list, new_token);
}


t_token *create_token_q_case_and_export(char **line, t_token *token_lst)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return(d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return(s_quote_case(line));
	if(ft_strncmp("export", token_lst->token, 6) == 0)
	{
		token_lst->token_type = EXPORT;
		return(create_export_token(*line));
	}
	else
		return (create_token(*line))
}


void tokeniser_for_export(t_token *token_lst, char *line)
{
	t_token *new_token;
	while(*line)
	{
		if (skip_whitespace_and_eof(&line) == false)
			break;
		new_token = create_token_q_case_and_export(&line, token_lst);
		tokenadd_back(&token_lst, new_token);
		line = update_export_line(line);
	}
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


