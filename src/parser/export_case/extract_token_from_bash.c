/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_from_bash.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:07:32 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:18:08 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


char *extract_var_value(char *env_str, int start_pos)
{
    char *tmp_token;
    char *new_token;
    new_token = ft_strdup("");
    if (!new_token)
        return (NULL);
    while (env_str[start_pos] != '\0')
    {
        tmp_token = ft_charjoin(new_token, env_str[start_pos]);
        free(new_token);
        new_token = tmp_token;
        start_pos++;
    }
    return (new_token);
}

// Main function to find environment variable value
char *get_var_from_env(char **src, char *token_no_dollar)
{
    int i;
    int var_len;
    char *found_token;
    char *tmp;

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
