/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:57:23 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/15 11:34:01 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_config* get_config(void)
{
	static t_config config ;
	return (&config);
}


void	init_config(t_config *config, char **envp)
{
	get_config
	//config->token_lst = NULL;
	(void)envp;
}
