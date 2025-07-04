
#include "executer.h"

char	**ft_delete_old_pwd(char **envp)
{
	int		max;
	int		i;
	int		j;
	char	**newenvp;

	max = 0;
	i = 0;
	j = 0;
	while (envp[max] != NULL)
		max++;
	newenvp = (char **)malloc(max * sizeof(char *));
	if (newenvp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		{
			newenvp[j] = ft_strdup(envp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	newenvp[j] = NULL;
	//envp = newenvp;
	return (newenvp);
}

char	**ft_add_old_pwd(char **envp)
{
	int		max;
	int		i;
	char	**newenvp;

	max = 0;
	i = 0;
	while (envp[max] != NULL)
		max++;
	newenvp = (char **)malloc((max + 2) * sizeof(char *));
	if (newenvp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
			newenvp[max] = ft_strjoin("OLD", envp[i]);
		newenvp[i] = envp[i];
		i++;
	}
	newenvp[max + 1] = NULL;
	//envp = newenvp;
	return (newenvp);
}

char	**ft_add_pwd(t_cmd_node *cmd_node, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			if (ft_strlen(envp[i]) > 5)
				envp[i] = ft_strjoin(envp[i], "/");
			envp[i] = ft_strjoin(envp[i], cmd_node->cmd[1]);
			if (envp[i][ft_strlen(envp[i]) - 1] == '/')
				envp[i][ft_strlen(envp[i]) - 1] = '\0'; //can break maybe
		}
		i++;
	}
	return (envp);
}
