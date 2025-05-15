



// to do 
 //   var= als eigene Variable  -> nicht var=cat und dann noch mal 'cat Makefile...'
 //

// zwischen cmd und Txt unterscheiden
// also zwischen echten cmds und random text 
// dann random text entfernen aus tokenliste entfernen bei export ?./m

#include "minishell.h"
#include "parser.h"

/*
aus "export var=\"cat Makefile | grep <\" ";

| token: 'export' | token_type: 0 
| token: 'var=cat' | token_type: 0 
| token: 'cat Makefile | grep <' | token_type: 0 

correct muss weiter ausdifferenzieren 
woerter ohne = werden ignoriert

*/

// koennten auch neue tokenliste zuruck geben und andere freen...

bool check_for_equal_sign(t_token *current_token)
{
    int i;

    i = 0;
    while(current_token->token[i])
    {
        if (ft_strncmp ("=", &current_token->token[i], 1) == 0)
		    return (true);
        i++;
    }
    return(false);
}


// A B C 

// B1 B2 B3 
// hello var oder cat Makefile
t_token *split_token_in_sub_token(t_token *current_token, t_token *chain)
{
    t_token *sub_token;
    t_token *head_subtoken;
    t_token *main_token_lst;

    main_token_lst = current_token->next;

    sub_token = tokeniser(current_token->token);
    if (!sub_token)
        return (main_token_lst);
    head_subtoken= sub_token;
    while(sub_token->next)
        sub_token = sub_token->next;
    sub_token->next = chain;
    return (head_subtoken);
}

t_token *create_token_splited(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token(content);
	new_token->token_type = get_token_type(content);
	new_token->next = NULL;
	return (new_token);
	// tokenadd_back(get_config()->token_list, new_token);
}

void delete_token(t_token *delete_token)
{
    if (delete_token == NULL)
        return;
    free(delete_token->token);
    free(delete_token);
}

// static bool check_for_whitespace(char *str)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         if(ft_strchr("\t\n\v\f\r " , *str[i]) == NULL)
// 		    return (true);
//     }
//     return (false);
// }

// static bool check_multi_tok_in_call_saved_var(t_token *token_lst)
// {
//     t_token *current_token;
//     seperate_token bool;
//     token_lst = current_token;

//     while(current_token && current_token->next)
//     {
//         if(current_token->token_type == CALL_SAVED_VAR)
//         {
//             if(current_token->next)
//             {
//                 current_token= current_token->next;
//                 if (check_for_whitespace(current_token->token) == true)
//                     return(seperate_token = true);
//             }
//         }
//     }
// }


void handle_export(t_token *token_lst)
{
    t_token *node_to_delete;
    t_token *node_to_jump_after;
    t_token *new_tokens;

    while(token_lst && token_lst->next)
    {
        if(token_lst->token_type == CALL_SAVED_VAR)
        {
            node_to_delete = token_lst->next;// "echo world"
            if(token_lst->next->next)
                node_to_jump_after = NULL;
            else
                node_to_jump_after = token_lst->next->next;
            new_tokens = split_token_in_sub_token(token_lst->next, node_to_jump_after);
            delete_token(node_to_delete);
            token_lst->next = new_tokens; // aber der next->pointer von world ist leer
            while(token_lst && token_lst->next && node_to_jump_after != NULL)
            {
                if(token_lst != node_to_jump_after)
                    token_lst= token_lst->next;
            }
        }
        token_lst = token_lst->next;// zwei nodes weiter wenn node gesplitted wurde
    }
}

    // wenn invalid_identiver 
    // get_exit_codes()->last_exit_code = invalid_identifier;
    // return;

    // wenn es glatt laeuft
    // get_exit_codes()->last_exit_code = ec_sucess;
    // return;


