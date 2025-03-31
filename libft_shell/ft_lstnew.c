/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:29:40 by poverbec          #+#    #+#             */
/*   Updated: 2024/12/09 11:40:49 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
allocates (with malloc(3)) and returns a new node. 
The member variable ’content’ is initialized with 
the value of the parameter 
’content’. The variable ’next’ is initialized to NULL.
*/

t_list	*ft_lstnew(void	*content)
{
	t_list	*node;

	node = malloc (sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = 0;
	return (node);
}
