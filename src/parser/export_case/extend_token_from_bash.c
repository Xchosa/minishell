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
            token_lst->token = get_var_from_env(bash->env,saved_var_without_$);
            free(saved_var_without_$);
            if(token_lst->next == NULL)
                return;
        }
        token_lst = token_lst->next;
    }
}



// bash-3.2$ echo $USER
// poverbec


// poverbec@3-E-23 minishell % echo 'Hallo $USER '
// Hallo $USER
// poverbec@3-E-23 minishell % echo "Hallo $USER"
// Hallo poverbec