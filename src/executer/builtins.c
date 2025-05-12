/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:27:44 by tschulle          #+#    #+#             */
/*   Updated: 2025/05/12 16:27:47 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to do: cd (only relative or absolute)  export, unset, env, exit
#include "../../inc/executer.h"
#include "../../inc/minishell.h"

void	ft_echo(t_cmd_node *cmd_node)
{
	int	i;

	i = 1;
	if (ft_strncmp("-n", cmd_node->cmd[1], 2) == 0)
		i++;
	while (cmd_node->cmd[i] != NULL)
	{
		ft_printf("%s", cmd_node->cmd[i]);
		if (cmd_node->cmd[i + 1] != NULL)
			ft_printf("\n");
		i++;
	}
	if (!(ft_strncmp("-n", cmd_node->cmd[1], 2) == 0))
		ft_printf("\n");
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
}

void	ft_cd(t_cmd_node *cmd_node, char **envp)
{
	if (chdir(cmd_node->cmd[1]) != 0)
		printf("Error\n");
	//nur fuer process
	//update envp
	//update prompt?
	//muss aussserhalb von child passieren??
}
