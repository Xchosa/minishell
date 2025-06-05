

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
// var1 ="ls -al >outfile"
// $var1 
// und echo $var1 ( ersters hat nicht mehr geklappt),
// t_token* tokenise_muliple_tok_from_env(t_token *token_lst, t_token *prev_token)
// {
//     t_token *split_token;
//     t_token *connect_token;
//     t_token *tail_token;
//     printf("About to tokenize: '%s'\n", token_lst->token);
//     // if(multiple_tokens(token_lst->token) == false)
//     //     return ;
//     split_token = tokeniser(token_lst->token);

    
//     printf("split_token\n");
//     iter_tokenlst(split_token, &print_tokenlst);


//     if(token_lst->next != NULL)
//         connect_token = token_lst->next;
//     else
//         connect_token = NULL;
//     t_token *tmp;
//     if(token_lst == token_lst->head ) // die zu splitende node ist die erste
//     {
//         tail_token = tokenlast(split_token);
//         while(token_lst != connect_token)
//         {
//             tmp = (token_lst->next);
//             // free(token_lst->token);
//             // free(token_lst);
//         }
//         tail_token->next = connect_token;
//         token_lst = split_token;
//         free(tmp);
//     }

//     else
//     {
//         prev_token->next = split_token;
//         tail_token = split_token;
//         tail_token = tokenlast(split_token);
//         while(token_lst != connect_token)
//         {
//             tmp = (token_lst->next);
//             // free(token_lst->token);
//             // free(token_lst);
//         }
//         tail_token->next = connect_token;
//         token_lst = split_token;
//         free(tmp);
//     }
// }
void tokenise_muliple_tok_from_env(t_token *token_lst, t_token *prev_token)
{
    t_token *split_token;
    t_token *connect_token;
    if(multiple_tokens(token_lst->token) == false)
        return ;
    split_token = tokeniser(token_lst->token);
    printf("split_token\n");
    iter_tokenlst(split_token, &print_tokenlst);
    if(token_lst->next)
        connect_token = token_lst->next;
    else
        connect_token = NULL;


        
    prev_token->next = split_token;
    split_token = tokenlast(split_token);
    split_token->next = connect_token;
}
