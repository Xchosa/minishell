
#include "executer.h"

// changed to real strcmp

char	*ft_strtolower(char *input)
{
	char	*output;
	int		i;

	i = 0;
	output = malloc(ft_strlen(input) + 1);
	if (output == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		output[i] = ft_tolower(input[i]);
		i++;
	}
	output[i] = '\0';
	free(input);
	return (output);
}

bool	ft_execute_builtin(t_cmd_node *cmd_node, char **envp)
{
	bool	check;

	cmd_node->cmd[0] = ft_strtolower(cmd_node->cmd[0]);
	if (cmd_node->cmd[0] == NULL)
		return false; //oder so
	check = false;
	if (ft_strcmp("echo", cmd_node->cmd[0]) == true)
		check = ft_echo(cmd_node, envp);
	if (ft_strcmp("pwd", cmd_node->cmd[0]) == true)
		ft_pwd(envp);
	if (ft_strcmp("env", cmd_node->cmd[0]) == true)
		ft_env(envp);
	if (ft_strcmp("cd", cmd_node->cmd[0]) == true)
		ft_cd(cmd_node, envp); // wenn der path nicht existiert failt es, hier drin error message, unten exit
	if (ft_strcmp("export", cmd_node->cmd[0]) == true)
		ft_export(cmd_node, envp);
	if (ft_strcmp("exit", cmd_node->cmd[0]) == true)
		ft_exit(cmd_node);
	if (ft_strcmp("unset", cmd_node->cmd[0]) == true)
		ft_unset(cmd_node, envp);
	// else
	// {
	// 	ft_putstr_fd("not a valid here executable", STDERR_FILENO);
	// 	return check; // echooooo hallo aport 
	// }
	return check;
}

// 