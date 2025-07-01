/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:15:44 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/01 10:52:01 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


char	*ft_give_pointer_to_path(char **envp)
{
	int		i;
	char	*to_path;

	i = 0;
	to_path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			to_path = envp[i];
		i++;
	}
	if (to_path == NULL)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		to_path++;
		i++;
	}
	return (to_path);
}

char	*ft_getpath(char *command, char **envp)
{
	char	*to_path;
	int		i;
	char	**arr;
	char	*tmp;
	char	*full;

	to_path = ft_give_pointer_to_path(envp);
	if (to_path == NULL)
		return (NULL);
	i = 0;
	arr = ft_split(to_path, ':');
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		tmp = ft_strjoin(arr[i], "/");
		full = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (ft_free_array(arr), full);
		i++;
		free(full);
	}
	return (ft_free_array(arr), NULL);
}
