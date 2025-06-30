
#include "executer.h"

// changed to real strcmp
void	ft_execute_builtin(t_cmd_node *cmd_node, char **envp)
{
	//ft_tolower make everything to lowerletters?
	if (ft_strcmp("echo", cmd_node->cmd[0]) == true)
		ft_echo(cmd_node, envp);
	if (ft_strcmp("pwd", cmd_node->cmd[0]) == true)
		ft_pwd(envp);
	if (ft_strcmp("env", cmd_node->cmd[0]) == true)
		ft_env(envp);
	if (ft_strcmp("cd", cmd_node->cmd[0]) == true)
		ft_cd(cmd_node, envp);
	if (ft_strcmp("export", cmd_node->cmd[0]) == true)
		ft_export(cmd_node, envp);
	if (ft_strcmp("exit", cmd_node->cmd[0]) == true)
		ft_exit(cmd_node);
	if (ft_strcmp("unset", cmd_node->cmd[0]) == true)
		ft_unset(cmd_node, envp);
}

