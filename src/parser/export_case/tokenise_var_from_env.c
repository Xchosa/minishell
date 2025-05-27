

#include "parser.h"
#include "minishell.h"


char *handle_mulit_token(char *line)
{
    while (*line && (ft_isalnum(*line) || special_char_no_divider_no_eq(*line)))
        line++;
    return (line);
}

char *skip_divider_without_space(char *line)
{
	if (ft_strncmp ("|", line, 1) == 0)
		line++;
	else if(ft_strncmp ("<", line, 1) == 0)
	{
        line++;
        if(ft_strncmp ("<", line, 1) == 0)
            line++;
    }
	else if (ft_strncmp (">", line, 1) == 0)
	{
        if(ft_strncmp (">", line, 1) == 0)
            line++;
    }
	else if (ft_strncmp (";", line, 1) == 0)
		line++;
	return (line);
}

void tokenise_muliple_tok_from_env(t_token *token_lst, t_token *prev_token)
{
    t_token *split_token;
    t_token *connect_token;
    printf("var found %s\n ", token_lst->token);
    if(multiple_tokens(token_lst->token) == false)
        return ;
    
    if(token_lst->next)
        connect_token = token_lst->next;
    else
        connect_token = NULL;
    split_token = tokeniser(token_lst->token);
    prev_token->next = split_token;
    while(split_token->next)
    {
        split_token = split_token ->next;
    }
    split_token->next = connect_token;
}

