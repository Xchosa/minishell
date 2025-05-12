



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
t_token *split_token_in_sub_token(t_token *current_token)
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
    sub_token->next = main_token_lst;
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

void handle_export(t_token *token_lst)
{
    t_token *current_token;
    t_token *node_to_delete;
    t_token *new_tokens;
    current_token = token_lst;
    
    while(current_token->next)
    {
        if(current_token->head->token_type==EXPORT)
        {
            if(check_for_equal_sign(current_token->next)== true)
            {
                current_token->token_type= Export_var; // var1
                current_token = current_token->next; // =
                node_to_delete = current_token->next;// echo world
                new_tokens = split_token_in_sub_token(current_token->next);
                delete_token(node_to_delete);
                current_token->next = new_tokens; // aber der next->pointer von world ist leer
                current_token = current_token->next;
            } 
        }
        current_token = current_token->next;// zwei nodes weiter wenn node gesplitted wurde
    }
}

    // wenn invalid_identiver 
    // get_exit_codes()->last_exit_code = invalid_identifier;
    // return;

    // wenn es glatt laeuft
    // get_exit_codes()->last_exit_code = ec_sucess;
    // return;


