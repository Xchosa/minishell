/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/30 14:23:03 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


void skip_whitespace(char **line)
{
	while(*line)
	{
		if(ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break;
		(*line)++;
	}
}

bool skip_whitespace_and_eof(char **line)
{
	bool not_eof;
	not_eof = true;
	while(**line != '\0')
	{
		if(ft_strchr("\t\n\v\f\r " , **line) == NULL)
			break;
		(*line)++;
	}
	if(**line == '\0')
	{
		return(not_eof = false);
	}
	return(not_eof);
	
}
// bool skip_whitespace_and_eof(char **line)
// {
//     // Skip all whitespace characters
//     while(**line != '\0' && ft_strchr("\t\n\v\f\r ", **line) != NULL)
//         (*line)++;
    
//     // Return false if we reached the end of string, true otherwise
//     return (**line != '\0');


bool	check_for_divider_without_space(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	return (false);
}
bool	check_for_divider_with_space(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
	return (false);
}


bool	not_single_divider(char c)
{
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	return (false);
}


char 	*ft_charjoin(char const *dst, char const src_char)
{
	char	*newstr;
	size_t	i;	
	size_t	strlen_dst;

	i = 0;
	
	strlen_dst = ft_strlen(dst);

	newstr = (char *)malloc(((strlen_dst + 2) * (sizeof(char))));
	if (newstr == NULL)
		return (NULL);
	while (i < strlen_dst)
	{
		newstr[i] = dst[i];
		i++;
	}
	newstr[i] = src_char;
	newstr[i + 1] = '\0';
	// printf("newstr: %s \n", newstr);
	return (newstr);
}

bool	find_divider_until_whitespace_or_eof(char c) // true
{
	if (c == '\0') // if end of line true 
		return (false);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != false) // if space true
		return (false);
	if (check_for_divider_without_space(c) == true)// if | true return true
		return (true);
	return (false);
}

bool	char_is_alpha_nbr_and_no_whitespace(char c)
{
	if (ft_isalnum(c) == true)
		return (true);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != NULL)
		return (true);
	if (ft_strnstr("-", &c, 1) != NULL)
		return (true);
	return (false);
}


