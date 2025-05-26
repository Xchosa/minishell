/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:33:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/29 09:35:03 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "minishell.h"

// vor handle export
// new string muss nicht mehr getokenised werden 

// nach dem ersten Tokeniser


// issue finds for USER :Username=poverbec and prints out ame=poverbec

// original_token = ft_strjoin("$", token_no_dollar);
//     if (ft_strncmp(token_no_dollar, "USER", 4)== 0)
//         original_token = ft_strjoin(token_no_dollar, "NAME");

char* get_var_from_env(char **src, char *token_no_dollar)
{
	int i;
    int j;
    char *new_token;
	char *tmp_token;
    char *original_token;
    
    original_token = ft_strjoin("$", token_no_dollar);
	i = 0;
    j = ft_strlen(token_no_dollar);
	while(src[i])
	{
		if((ft_strncmp(src[i], token_no_dollar, j) == 0))
        {
            printf("%d  :%s\n", i, src[i]);
            token_no_dollar++;
            j++;
            new_token =ft_strdup("");
            while((src[i])[j] != '\0')
	        {
		        tmp_token = ft_charjoin(new_token, (src[i][j]));
		        free(new_token);
                new_token = tmp_token;
		        j++;
	        }
            return (new_token);
        }
		i++;
	}
    return(original_token);
}
// 
// if(ft_strncmp("USER", saved_var_without_$, 4) == 0)
//         change_spelling_USER_to_USERNAME(saved_var_without_$);
// void change_spelling_USER_to_USERNAME(char *saved_var_without_$)
// {
//     free(saved_var_without_$);
//     saved_var_without_$ = ft_strdup("USERNAME");
// }

static bool check_input_user(char *token)
{
    if((ft_strncmp(token, "USERNAME", 8) == 0))
        return (false);
    if((ft_strncmp(token, "USER", 4) == 0))
        return (true);
    return (false);
}

static char* handle_user(char **src)
{
    int i;
    int j;
    char *new_token;
	char *tmp_token;
    
	i = 0;
    j = 0;
    while(src[i])
	{
		if((ft_strncmp(src[i], "USERNAME", 8) == 0) )
        {
            j += 9;
            new_token =ft_strdup("");
            while((src[i])[j] != '\0')
	        {
		        tmp_token = ft_charjoin(new_token, (src[i][j]));
		        free(new_token);
                new_token = tmp_token;
		        j++;
	        }
            return (new_token);
        }
		i++;
	}
    return(ft_strdup("$USER"));
}


// $USER oder $h > poverbec or world 

void extend_saved_export_var(t_token *token_lst)
{
    char *saved_var_without_$;
    t_bash *bash;
    
    bash = get_bash();

    while(token_lst)
    {
        if(token_lst->token_type == CALL_SAVED_VAR)
        {
            saved_var_without_$ = ft_strdup(token_lst->token + 1);
            free(token_lst->token);
            if(check_input_user(saved_var_without_$) == true)
                token_lst->token = handle_user(bash->env);
            else
                token_lst->token = get_var_from_env(bash->env,saved_var_without_$);
            free(saved_var_without_$);
            if(token_lst->next == NULL)
                return;
        }
        token_lst = token_lst->next;
    }
}
