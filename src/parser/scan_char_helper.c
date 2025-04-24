/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/24 13:22:43 by poverbec         ###   ########.fr       */
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

bool	check_for_divider(char c)
{
	if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	// if (ft_strncmp (" ", &c, 1) == 0)
	// 	return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
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
	if (check_for_divider(c) == true)// if | true return true
		return (true);
	return (false);
}

bool	char_is_alpha_nbr_and_no_whitespace(char c)
{
	if (ft_isalnum(c) == true)
		return (true);
	if (ft_strnstr("\r\n\v\t ", &c, 1) != NULL)
		return (true);
	return (false);
}

char	*update_line(char *line)
{
	int	i;

	i = 0;
	skip_whitespace(&line);
	if(ft_strncmp( "\"", line, 1) == 0)
	{
		line++;
		while(ft_strncmp( "\"", line, 1) != 0) // update until ""
 		{
 			line++;
	 	}
		line++;
		return (&line[i]); // i unnoetig
	}
	// old function
	while (*line && check_for_divider(*line) == true && *line != ' ') 
        line++;
	while (*line && ft_isalnum(*line))
        line++;
	return	(&line[i]);
}


// char	*update_line_with_quotes(char *line)
// {
// 	int	i;

// 	i = 0;
// 	(*line)++
// 	while(ft_strncmp( "\"", &line[i+1], 1 == 0))
// 	{
// 		line++;
// 	}
// 	return(&line[i]);
// }
