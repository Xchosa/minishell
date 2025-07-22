
#include "executer.h"

char	*ft_strtolower(char *input)
{
	char	*output;
	int		i;

	i = 0;
	
	output = malloc(ft_strlen(input) + 1);
	if (output == NULL)
	{
		ft_putendl_fd("malloc failed\n", 2);
		return (NULL);
	}
	while (input[i] != '\0')
	{
		output[i] = ft_tolower(input[i]);
		i++;
	}
	output[i] = '\0';
	free(input);
	return (output);
}

void	ft_execute_builtin(t_cmd_node *cmd_node, char **envp)
{
	cmd_node->cmd[0] = ft_strtolower(cmd_node->cmd[0]);
	if (cmd_node->cmd[0] == NULL)
	{
		get_exit_codes()->last_exit_code = 1;
		return ;
	}
	if (ft_strcmp("echo", cmd_node->cmd[0]) == true)
		ft_echo(cmd_node);
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
}
