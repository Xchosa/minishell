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

void	ft_echo(t_cmd_node *cmd_node, char **envp)
{
	int	i;

	i = 1;
	(void)envp;
	if (ft_strncmp("-n", cmd_node->cmd[1], 2) == 0)
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
	(void)envp;
	if (chdir(cmd_node->cmd[1]) != 0)
		printf("Error\n");

	//nur fuer process
	//update envp
	//update prompt?
	//muss aussserhalb von child passieren??
}

int	ft_isnum(char *s)
{
	int 	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
		 	return (1);
	}
	return (0);
}

void	ft_exit(t_cmd_node *cmd_node)
{
	int	re;

	re = 0;
	ft_printf("exit\n");
	if (cmd_node->cmd[1] != NULL)
	{
		if (ft_isnum(cmd_node->cmd[1]) == 0)
		{
			re = ft_atoi(cmd_node->cmd[1]);
			if (cmd_node->cmd[2] != NULL)
			{
				ft_printf("ptsh: exit: too many arguments"); //kommt nach pipe echo??
				//set exit code
				return ;
			}
		}
		else
			ft_printf("ptsh: exit: %s: numeric argument required", cmd_node->cmd[1]);
	}
	exit(re);
}
