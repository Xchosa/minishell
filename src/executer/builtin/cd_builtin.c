#include "executer.h"

char	**ft_add_absolute_path(t_cmd_node *cmd_node, char **envp)
{
	int	i;
	char	*buf;
	char	*re;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			buf = envp[i];
			re = ft_strjoin("PWD=", cmd_node->cmd[1]);
			if (re == NULL)
				return (NULL);
			envp[i] = re;
			free(buf);
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
	//int	times;
	(void)cmd_node;

	i = 0;
	//times = (ft_strlen(cmd_node->cmd[1]) + 1) / 3; //probably bad and should use split and while loop
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			len = ft_strlen(envp[i]);
			//while (times > 0)
			//{
				while (envp[i][len - 1] != '/') //can segfault if fals input, parten from root?
					len--;
				len--;
			//	times--;
			//}
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
//	newpwd = malloc(sizeof(char *));
//	if (newpwd == NULL) 
//		return (NULL);		nicht noetig? aber malloc check unten
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], "PWD", 3) == 0)
		{
		//	free(envp[j]); //maybe
			break ;
		}
		j++;
	}
	home = get_home_path(envp);
	if (home == NULL)
		ft_putendl_fd("shell: cd: HOME not set", 2); // and return NULL and check for it
	else
	{
		newpwd = ft_strjoin("PWD=", home);
		envp[j] = newpwd;
	}
	return (envp);
}

char	**ft_add_relative_path(t_cmd_node *cmd_node, char **envp)
{
	char	**path_array;
	int		i;

	i = 0;
	path_array = ft_split(cmd_node->cmd[1], '/' );
	while (path_array[i] != NULL)
	{
		if (ft_strncmp("~", path_array[0], 1) == 0)
			envp = ft_add_tilde(envp); //wohl bloedsinn kommt so nicht als token?
		else if (ft_strncmp("..", path_array[i], 2) == 0)
			envp = ft_add_parent(cmd_node, envp);
		else if (!(ft_strncmp(".", path_array[i], 1) == 0))
			envp = ft_add_pwd(path_array[i], envp);
		i++;
	}
	return (envp);
}

void	ft_update_env_cd(t_cmd_node *cmd_node, char **envp)
{
	if (there_is_env_var(envp, "OLDPWD=") == true)
		envp = ft_delete_old_pwd(envp);
	if (envp == NULL)
		return ;
	envp = ft_add_old_pwd(envp);
	if (cmd_node->cmd[1] == NULL)
		envp = ft_add_tilde(envp);
	else if (ft_strncmp(get_home_path(envp), cmd_node->cmd[1], 100) == 0) //oder pauls strcmp ? wie funktioniert die? muessen sie gleich lang sein?
		envp = ft_add_tilde(envp);
	else if (ft_strncmp("/", cmd_node->cmd[1], 1) == 0)
		envp = ft_add_absolute_path(cmd_node, envp); //do relative path
	else 
		envp = ft_add_relative_path(cmd_node, envp);
/*	else if (ft_strncmp("..", cmd_node->cmd[1], 2) == 0)
		envp = ft_add_parent(cmd_node, envp);
	else if (ft_strncmp(get_home_path(envp), cmd_node->cmd[1], 1) == 0)
		envp = ft_add_tilde(envp);
	else if (!(ft_strncmp(".", cmd_node->cmd[1], 10) == 0))
		envp = ft_add_pwd(cmd_node, envp); */
	get_bash()->env = envp; //und free die alte envp
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
	if (chdir(cmd_node->cmd[1]) != 0) //      ~/projects klappt hier nicht
	{
		get_exit_codes()->last_exit_code = 1;
		perror("shell");
		return ;
	}
	ft_update_env_cd(cmd_node, envp);
	get_exit_codes()->last_exit_code = 0;
}
