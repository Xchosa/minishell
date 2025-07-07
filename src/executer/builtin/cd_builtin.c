#include "executer.h"

char	**ft_add_absolute_path(t_cmd_node *cmd_node, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			envp[i] = ft_strjoin("PWD=", cmd_node->cmd[1]);
			if (envp[i][ft_strlen(envp[i]) - 1] == '/')
				envp[i][ft_strlen(envp[i]) - 1] = '\0'; //free here, maube break
		}
		i++;
	}
	return (envp);
}

char	**ft_add_parent(t_cmd_node *cmd_node, char **envp)
{
	int	i;
	int	len;
	int	times;

	i = 0;
	times = (ft_strlen(cmd_node->cmd[1]) + 1) / 3; //probably bad and should use split and while loop
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			len = ft_strlen(envp[i]);
			while (times > 0)
			{
				while (envp[i][len - 1] != '/') //can segfault if fals input, parten from root?
					len--;
				len--;
				times--;
			}
			if (len > 4)
				envp[i] = ft_substr(envp[i], 0, len);
			else
				envp[i] = ft_strdup("PWD=/");
		}
		i++;
	}
	return (envp);
}

char	**ft_add_tilde(char **envp)
{
	int		j;
	char	*newpwd;
	char	*home;

	j = 0;
	newpwd = malloc(sizeof(char *));
	if (newpwd == NULL)
		return (NULL);
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], "PWD", 3) == 0)
		{
			free(envp[j]); //maybe
			break ;
		}
		j++;
	}
	home = get_home_path(envp);
	newpwd = ft_strjoin("PWD=", home);
	envp[j] = newpwd;
	return (envp);
}

void	ft_update_env_cd(t_cmd_node *cmd_node, char **envp)
{
	envp = ft_delete_old_pwd(envp);
	envp = ft_add_old_pwd(envp);
	if (cmd_node->cmd[1] == NULL)
		envp = ft_add_tilde(envp);
	else if (ft_strncmp("/", cmd_node->cmd[1], 1) == 0)
		envp = ft_add_absolute_path(cmd_node, envp); //do relative path
	else if (ft_strncmp("..", cmd_node->cmd[1], 2) == 0)
		envp = ft_add_parent(cmd_node, envp);
	else if (ft_strncmp(get_home_path(envp), cmd_node->cmd[1], 1) == 0)
		envp = ft_add_tilde(envp);
	else if (!(ft_strncmp(".", cmd_node->cmd[1], 10) == 0))
		envp = ft_add_pwd(cmd_node, envp);
	get_bash()->env = envp;
}

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
