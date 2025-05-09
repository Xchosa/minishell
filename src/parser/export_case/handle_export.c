





// to do 
 //   var= als eigene Variable  -> nicht var=cat und dann noch mal 'cat Makefile...'
 //

// zwischen cmd und Txt unterscheiden
// also zwischen echten cmds und random text 
// dann random text entfernen aus tokenliste entfernen bei export ?

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

void handle_export(t_token *token_lst)
{
    t_token *current_token;
    current_token = token_lst;
    
    while(current_token->next)
    {
        if(current_token->head->token_type==EXPORT)
        {
            // if token alpha to begin  dann =cat 
                    // token-type call saved _var 
             //   if token alpha to beginn dann = und dann \" 
                    // ganzen token erneut tokenisen // next pointer correct updaten
                
                // was allein steht mit 

        }


        current_token = current_token->next;
    }
    // wenn invalid_identiver 
    // get_exit_codes()->last_exit_code = invalid_identifier;
    // return;

    // wenn es glatt laeuft
    // get_exit_codes()->last_exit_code = ec_sucess;
    // return;
}

