#include "executer.h"

char	*get_home_path(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("HOME=", envp[i], 5) == 0)
			break ;
		i++;
	}
	home = envp[i];
	i = 0;
	if (home == NULL)
		return (NULL); // exitcode here maybe?
	while (i < 5)
	{
		home++;
		i++;
	}
	return (home);
}

bool	there_is_env_var(char **envp, char *env_var)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], env_var, ft_strlen(env_var)) != 0)
		{
			i++;
			j++;
		}
		else
			i++;
	}
	if (i == j)
		return (false);
	else
		return (true);
}

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
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			newenvp[j] = envp[i];
			i++;
			j++;
		}
		else
			i++;
	}
	newenvp[j] = NULL;
	free(envp);
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
	free(envp);
	return (newenvp);
}

char	**ft_add_pwd(char *dir, char **envp) //protect malloc
{
	int		i;
	char	*buf;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
		{
			buf = envp[i];
			if (ft_strlen(envp[i]) > 5)
			{
				envp[i] = ft_strjoin(envp[i], "/");
				free(buf);
				buf = envp[i];
			}
			envp[i] = ft_strjoin(envp[i], dir);
			if (envp[i][ft_strlen(envp[i]) - 1] == '/')
			envp[i][ft_strlen(envp[i]) - 1] = '\0'; //can break maybe
			free(buf);
		}
		i++;
	}
	return (envp);
}
