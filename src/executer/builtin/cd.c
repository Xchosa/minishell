/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:41:44 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/22 13:41:47 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_cd(t_cmd_node *cmd_node, char **envp)
{
	if (cmd_node->cmd[1] == NULL)
	{
		chdir(get_home_path(envp));
		ft_update_env_cd(cmd_node, envp);
		get_exit_codes()->last_exit_code = 0;
		return ;
	}
	if (chdir(cmd_node->cmd[1]) != 0)
	{
		get_exit_codes()->last_exit_code = 1;
		perror("shell");
		return ;
	}
	ft_update_env_cd(cmd_node, envp);
	get_exit_codes()->last_exit_code = 0;
}
