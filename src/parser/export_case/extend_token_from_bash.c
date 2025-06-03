/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_token_from_bash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:33:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/03 15:29:53 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "minishell.h"


static char *extract_var_value(char *env_str, int start_pos)
{
    char *tmp_token;
    char *new_token;
    new_token = ft_strdup("");
    if (!new_token)
        return (NULL);
    // printf("env string %s\n", env_str + start_pos);
    while (env_str[start_pos] != '\0')
    {
        tmp_token = ft_charjoin(new_token, env_str[start_pos]);
        free(new_token);
        new_token = tmp_token;
        start_pos++;
    }
    // printf("env string after %s\n", new_token); 
    return (new_token);
}

// Main function to find environment variable value
char *get_var_from_env(char **src, char *token_no_dollar)
{
    int i;
    int var_len;
    char *original_token;
    char *found_token;
    char *tmp;

    original_token = ft_strjoin("$", token_no_dollar);
    tmp = ft_strjoin(token_no_dollar, "=");
    if (!tmp)
        return (NULL);
    var_len = ft_strlen(tmp);
    i = 0;
    while (src[i])
    {
        if (ft_strncmp(src[i], tmp, var_len) == 0)
        {
            found_token = extract_var_value(src[i], var_len);
            free(original_token);
            free(tmp);
            return (found_token);
        }
        i++;
    }
    free(tmp);
    return (ft_strdup(""));
}

char *get_home_directory(char **src)
{
	int i;
	int home_len;
	
	home_len = ft_strlen("HOME=");
	i = 0;
	while(src[i])
	{
		if(ft_strncmp("HOME=", src[i], home_len) == 0)
		{
			return(extract_var_value(src[i], home_len));
		}
		i++;
	}
	return(ft_strdup(""));
}

void reset_token_get_home_directory(t_token **token_lst, char **src)
{
	free((*token_lst)->token);
	(*token_lst)->token = get_home_directory(src);
	(*token_lst)->token_type = TEXT;
}

void extend_saved_export_var(t_token *token_lst)
{
    char *saved_var_without_$;
    t_bash *bash;
    t_token *prev_token;

    bash = get_bash();
    prev_token = NULL;
    while(token_lst)
    {
		if(token_lst->token_type == Tilde)
			reset_token_get_home_directory(&token_lst,bash->env);
        else if(token_lst->token_type == CALL_SAVED_VAR)
        {
            saved_var_without_$ = ft_strdup(token_lst->token + 1);
            free(token_lst->token);
            token_lst->token = get_var_from_env(bash->env,saved_var_without_$);
            free(saved_var_without_$);
            tokenise_muliple_tok_from_env(token_lst, prev_token);
            if(token_lst->next == NULL)
                return;
        }
        prev_token = token_lst;
        token_lst = token_lst->next;
    }
}

