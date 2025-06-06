/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_token_from_bash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:33:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:40:34 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "minishell.h"



void reset_token_get_home_directory(t_token **token_lst, char **src)
{
	free((*token_lst)->token);
	(*token_lst)->token = get_home_directory(src);
	(*token_lst)->token_type = TEXT;
}

void reset_token_get_var_from_env(t_token **token_lst, char **src)
{
	char *str_until_dollar;
	char *tmp_token;
	char *old_token;
    char *env_str;
	int i;
	// ec$t
	i = 0;
	old_token = ft_strdup((*token_lst)->token);
	free(((*token_lst)->token));
	str_until_dollar = ft_strdup("");
	while(strncmp(&old_token[i], "$", 1) != 0)
	{
		tmp_token = ft_charjoin(str_until_dollar,old_token[i]);
		free(str_until_dollar);
		str_until_dollar = tmp_token;
		i++;
	}
	env_str = get_var_from_env(src,old_token + i+1);
    // printf("var found fpr $var: '%s'\n ", env_str);
	(*token_lst)->token = ft_strjoin(str_until_dollar, env_str);
    (*token_lst)->token_type = TEXT;
	free(str_until_dollar);
}

void extend_saved_export_var(t_token *token_lst)
{
    char    *saved_var;
    t_bash  *bash;
    t_token *prev_token;

    bash = get_bash();
    prev_token = NULL;
    while(token_lst)
    {
		if(token_lst->token_type == Tilde)
			reset_token_get_home_directory(&token_lst,bash->env);
        else if(token_lst->token_type == CALL_SAVED_VAR)
        {
            saved_var = ft_strdup(token_lst->token + 1);
            free(token_lst->token);
            token_lst->token = get_var_from_env(bash->env,saved_var);
            free(saved_var);
			printf("before tokensise mulitple\n");
			iter_tokenlst(token_lst, &print_tokenlst);
			printf("do i come here?\n");\\ yes
            tokenise_muliple_tok_from_env(&token_lst, prev_token);
			printf("after tokensise mulitple\n");
			iter_tokenlst(token_lst, &print_tokenlst);
			// if(prev_token == NULL)
			// 	return;
            if(token_lst->next == NULL)
                return;
        }
		else if(token_lst->token_type == Mix_Export_var)
		{
			reset_token_get_var_from_env(&token_lst, bash->env);
            tokenise_muliple_tok_from_env(&token_lst, prev_token);
    		if(token_lst->next == NULL)
				return;
		}
		printf("split_token\n");
		iter_tokenlst(token_lst, &print_tokenlst);
        prev_token = token_lst;
        token_lst = token_lst->next;
    }
}





// void extend_saved_export_var(t_token *token_lst)
// {
//     char	*saved_var;
//     t_bash	*bash;
//     t_token *prev_token;
// 	t_token *head_token;

//     bash = get_bash();
// 	head_token =  token_lst;
//     prev_token = NULL;
// 	while(prev_token == NULL || ())
// 		while(token_lst)
// 		{
// 			if(token_lst->token_type == Tilde)
// 				reset_token_get_home_directory(&token_lst,bash->env);
// 			else if(token_lst->token_type == CALL_SAVED_VAR)
// 			{
// 				saved_var = ft_strdup(token_lst->token + 1);// without $sign 
// 				free(token_lst->token);
// 				token_lst->token = get_var_from_env(bash->env,saved_var);
// 				free(saved_var);
// 				tokenise_muliple_tok_from_env(&token_lst, prev_token);
// 				if(prev_token == NULL)
// 					head_token = token_lst;
// 				if(token_lst->next == NULL)
// 					return;
// 			}
// 			else if(token_lst->token_type == Mix_Export_var)
// 			{
// 				reset_token_get_var_from_env(&token_lst, bash->env);
// 				tokenise_muliple_tok_from_env(&token_lst, prev_token);
// 				if(token_lst->next == NULL)
// 					return;
// 			}
// 			printf("split_token\n");
// 			iter_tokenlst(token_lst, &print_tokenlst);
// 			prev_token = token_lst;
// 			token_lst = token_lst->next;
// 		}
// }

// void extend_saved_export_var(t_token *token_lst)
// {
//     char    *saved_var;
//     t_bash  *bash;
//     t_token *prev_token;
//     t_token *head_token;
//     bool list_modified;

//     bash = get_bash();
//     head_token = token_lst;
    
//     do {
//         list_modified = false;
//         prev_token = NULL;
//         token_lst = head_token;
        
//         while(token_lst)
//         {
//             if(token_lst->token_type == Tilde)
//             {
//                 reset_token_get_home_directory(&token_lst, bash->env);
//             }
//             else if(token_lst->token_type == CALL_SAVED_VAR)
//             {
//                 saved_var = ft_strdup(token_lst->token + 1);// without $sign 
//                 free(token_lst->token);
//                 token_lst->token = get_var_from_env(bash->env, saved_var);
//                 free(saved_var);
//                 tokenise_muliple_tok_from_env(&token_lst, prev_token);
                
//                 // Update head if the first token was replaced
//                 if(prev_token == NULL)
//                     head_token = token_lst;
                    
//                 list_modified = true;
//                 break; // Restart the loop
//             }
//             else if(token_lst->token_type == Mix_Export_var)
//             {
//                 reset_token_get_var_from_env(&token_lst, bash->env);
//                 tokenise_muliple_tok_from_env(&token_lst, prev_token);
                
//                 // Update head if the first token was replaced
//                 if(prev_token == NULL)
//                     head_token = token_lst;
                    
//                 list_modified = true;
//                 break; // Restart the loop
//             }
            
//             prev_token = token_lst;
//             token_lst = token_lst->next;
//         }
//     } while(list_modified);
    
//     printf("Final token list:\n");
//     iter_tokenlst(head_token, &print_tokenlst);
// }