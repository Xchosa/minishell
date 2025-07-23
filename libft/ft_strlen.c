/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:19:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/23 15:05:26 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
     The strlen() function computes the length of the string s.  The strnlen()
     function attempts to compute the length of s, but never scans beyond the
     first maxlen bytes of s.
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	// if (s == NULL)
	// 	return (0);
	if (*s == '\0')
		return('\0');
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
