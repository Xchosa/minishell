/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:21:58 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/17 15:24:01 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
Allocates (with malloc(3)) and returns 
an array of strings obtained by splitting
 ’s’ using the character ’c’ as a delimiter. 
The array must end with a NULL pointer.
*/

static size_t	count_sub_strings(char const *s, char c);
static char		**str_split(char **substring, char const *s, char c);
static void		free_string(char **str);

char	**ft_split(char const *s, char c)
{
	char	**substrings;
	size_t	nbr_strings;

	if (!s)
		return (NULL);
	nbr_strings = count_sub_strings(s, c);
	substrings = (char **)malloc((nbr_strings + 1) *(sizeof(char *)));
	if (!substrings)
		return (NULL);
	return (str_split(substrings, s, c));
}

static size_t	count_sub_strings(char const *s, char c)
{
	size_t	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			nbr++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (nbr);
}

char	**str_split(char **substring, char const *s, char c)
{
	size_t	a;
	size_t	len_substring;

	a = 0;
	while (*s)
	{
		if (*s != c)
		{
			len_substring = 0;
			while (s[len_substring] != '\0' && s[len_substring] != c)
				len_substring++;
			substring[a] = ft_substr(s, 0, len_substring);
			if (!substring[a])
				return (free_string(substring), NULL);
			a++;
			s += len_substring;
		}
		else
			s++;
	}
	return (substring[a] = NULL, substring);
}

static void	free_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
