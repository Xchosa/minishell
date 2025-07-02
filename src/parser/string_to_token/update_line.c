/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:57:07 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 16:09:20 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	pipe_or_simec(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("=", &c, 1) == 0)
		return (true);
	return (false);
}

int special_char_no_divider(char c)
{
	if (c == '-')
		return (1);
    // if (c == ' ')
	// 	return (1);
    if (c == '/')
		return (1);
	if (c == '=')
	 	return (1);
	if (ft_strchr(".,;!?*~$", c) != NULL)
		 return (1);
	return (0);
}
int special_char_no_divider_no_eq(char c)
{
	if (c == '-')
		return (1);
    if (c == '/')
		return (1);
	if (ft_strchr(".,;!?*~$", c) != NULL)
		return (1);
	return (0);
}

char *handle_dividers(char *line, bool *flag)
{
    while (*line && check_for_divider_with_space(*line) == true)
    {
        if (pipe_or_simec(*line) == true)
        {
            line++;
            *flag = true;
            return (line);
        }
        line++;
        *flag = true;
    }
    return (line);
}

bool check_for_space(char c)
{
    if (c == ' ')
		return (true);
    return false;
}
// tokeniser ohne update line...  echo hallo'world now' niemals handlbar 
// wenigstens das er trennt bei helleo
char *handle_regular_token(char *line)
{
    while (*line && (ft_isalnum(*line) || special_char_no_divider(*line)))
    {
        // if(check_for_space(*line) == true)
        //         return(line);
        line++;
    }
    return (line);
}

char *update_line(char *line, t_token *token)
{
    bool flag = false;
    char *updated_line;
    
    (void)token;// if token = $..
    skip_whitespace(&line);
    updated_line = handle_special_characters(line);
    if (updated_line)
        return (updated_line);
    line = handle_dividers(line, &flag);
    if (flag == false)
        line = handle_regular_token(line);
    return (line);
}

