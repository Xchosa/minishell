

#include "parser.h"
#include "minishell.h"


static bool equal_last(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
    }
    i--;
    if(ft_strncmp((str + i), "=", 1) == 0)
        return true;
    return (false);
}

// static char *update_line_ones(char *line)
// {
//     skip_whitespace(&line);
//     if(check_for_divider_without_space(*line) == false)
//     {
//         line = handle_mulit_token(line);
//         if(line)
//             return(NULL);
//         else
//             return(line);
//     }
//     line = skip_divider_without_space(line);
//     skip_whitespace(&line);
//         return(line);
//     return(line);

// }


bool multiple_tokens(char *line)
{
    bool multiple_token;
	t_token *cpy_tok;

    // int i;
    // i = 0;
	if (!line || *line == '\0')
		return(false);

    cpy_tok =tokeniser(line);
    if(cpy_tok == NULL)
    {
        free(cpy_tok);
        return(false);
    }
    if(cpy_tok->next == NULL)
    {
        free(cpy_tok);
        return(false);
        
    }
    free(cpy_tok);
    return(true);

	// cpy_tok = tokenlstnew(line);
    // printf("cpy toke: %s \n", cpy_tok->token);
	// if (!cpy_tok)
	// 	return (false);
    // if (ft_strncmp(cpy_tok->token, "$", 1) == 0)
    //     return(false);
    // line = update_line_ones(line);
    // // printf("line: %s\n", line);
	// if (line == NULL || *line == '\0')
    //     multiple_token = false;
    // else
    //     multiple_token = true;
    // free(cpy_tok);
    // printf("error in mulitple tok\n %d \n", multiple_token);
	return (multiple_token);
}


void append_export_str(t_token **curr_token)
{
    t_token *passed_position;

    passed_position = (*curr_token);
    while(*curr_token)
    {
        if ((*curr_token)->token_type == Export_var 
        && (*curr_token)->next 
        && (*curr_token)->next->token_type == TEXT 
        && equal_last((*curr_token)->token) == true)
        {
            if(multiple_tokens((*curr_token)->next->token) == true)
            {
                printf("extend tokens %s + %s \n", (*curr_token)->token, (*curr_token)->next->token);
                char *tmp_char= ft_strdup((*curr_token)->token);
                free((*curr_token)->token);
                (*curr_token)->token = ft_strjoin(tmp_char, (*curr_token)->next->token);
                (*curr_token)->next = (*curr_token)->next->next;
                free(tmp_char);
            }
        }
        (*curr_token) = (*curr_token)->next;
    }      
    (*curr_token) = passed_position;
}
