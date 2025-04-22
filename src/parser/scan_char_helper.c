/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/22 15:37:20 by poverbec         ###   ########.fr       */
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

char	*update_line(char *line)
{
	int	i;

	i = 0;
	if (*line && !ft_isalnum(*line)) {
        return (line + 1);
    }
	while (*line && ft_isalnum(*line))
        line++;
	return	(&line[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	strlen_s1;
	size_t	strlen_s2;

	strlen_s1 = ft_strlen(s1);
	strlen_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	newstr = (char *)malloc(((strlen_s1 + strlen_s2 + 1) * (sizeof(char))));
	if (newstr == NULL)
		return (NULL);
	while (i < strlen_s1)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (j < strlen_s2)
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}