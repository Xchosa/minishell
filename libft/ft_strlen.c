/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:19:42 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/06 13:32:05 by poverbec         ###   ########.fr       */
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
	if (*s == '\0')
		return('\0');
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
