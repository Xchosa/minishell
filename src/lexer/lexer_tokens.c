


#include "minishell.h"
#include "parser.h"

bool lex_check_for_correct_equal_sign(t_tocken *current_token)
{
    int i;

    i = 0;
    while(current_token->token[i])
    {
        if (ft_strncmp ("=", current_token->token[i], 1) == 0)
		{
            if(ft_isalpha(current_token->token[0]) == false) == 
                {
                    exit_code()->last_exit_code = invalid_identifier;
                    current_token->token_type = error;
                    return(false)
                }
        }
        i++;
    }
    return(true);
}




bool check_tokens(t_token *token_lst)
{
    t_token *current_token;
    current_token = token_lst;
    
    while(current_token->next)
    {
        if(current_token->head->token_type==EXPORT)
        {
            if(lex_check_for_equal_sign(current_token)== false)
                return(false);
        }
            // if token alpha to begin  dann =cat 
                    // token-type call saved _var 
             //   if token alpha to beginn dann = und dann \" 
                    // ganzen token erneut tokenisen // next pointer correct updaten
                
                // was allein steht mit 

        current_token = current_token->next;
    }
}