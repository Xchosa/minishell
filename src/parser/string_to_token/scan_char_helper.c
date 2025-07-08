/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:51:38 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/08 10:45:24 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	if (ft_strncmp ("\"", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("\'", &c, 1) == 0)
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


char 	*ft_charjoin(char *dst, char const src_char)
{
	char	*newstr;
	size_t	i;	
	size_t	strlen_dst;

	i = 0;
	strlen_dst = ft_strlen(dst);
	newstr = (char *)malloc(((strlen_dst + 2) * (sizeof(char))));
	if (newstr == NULL)
	{
		if(dst != NULL)
			free(dst);
		return (NULL);
	}
	while (i < strlen_dst)
	{
		newstr[i] = dst[i];
		i++;
	}
	newstr[i] = src_char;
	newstr[i + 1] = '\0';

	if(dst != NULL)
		free(dst);
	return (newstr);
}

