/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:35:14 by poverbec          #+#    #+#             */
/*   Updated: 2025/02/19 10:20:38 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

// str to integer
int	ft_atoi(const char *str)
{
	int	isneg;
	int	i;
	int	number;

	number = 0;
	i = 0;
	isneg = 1;
	while (str[i] == (' ') || ((str[i] >= 9) && str[i] <= 13))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			isneg *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * isneg);
}

// int	main(void)
// {
// 	char	*test;
// 	int		number;

// 	test = " -1234";
// 	number = ft_atoi(test);
// 	printf("%d", number);
// 	return (0);
// }
