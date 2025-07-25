/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:14:45 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/25 10:20:14 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
frees a 2D array
*/
void	ft_free_array(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
		i++;
	while (i >= 0)
	{
		free(arrays[i]);
		i--;
	}
	free(arrays);
}
