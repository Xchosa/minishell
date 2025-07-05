/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:27:44 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/05 14:49:57 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_echo(t_cmd_node *cmd_node) // muss auf write testen?
{
	int	i;

	i = 1;
	while (ft_strncmp("-n", cmd_node->cmd[i], 2) == 0)
		i++;
	while (cmd_node->cmd[i] != NULL)
	{
		if (ft_strncmp("$?", cmd_node->cmd[i], 2) == 0)
			ft_printf("%d", get_exit_codes()->last_exit_code);
		else
		 	ft_printf("%s", cmd_node->cmd[i]);
		if (cmd_node->cmd[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!(ft_strncmp("-n", cmd_node->cmd[1], 2) == 0))
		ft_printf("\n");
	get_exit_codes()->last_exit_code = 0;
}

void	ft_pwd(char **envp)
{
	char *pwd;
	int	i;

	i = 0;
	while(envp[i] != NULL)
	{
		if (ft_strncmp("PWD", envp[i], 3) == 0)
		{
			pwd = envp[i];
			break;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pwd++; 
		i++;
	}
	ft_printf("%s\n", pwd);
	get_exit_codes()->last_exit_code = 0;
}

void	ft_env(char **envp)
{
	int	i;
	i = 0;

	while (envp[i] != NULL)
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	get_exit_codes()->last_exit_code = 0;
}
