#include "executer.h"

void	ft_unset_var(char **envp, int j)
{
	char	**newenvp;
	int		size;
	int		i;
	char	*tmp;

	tmp = envp;
	size = 0;
	i = 0;
	while (envp[size] != NULL)
		size++;
	newenvp = (char **)malloc(size * sizeof(char *));
	while (i < size - 1)
	{
		if (i < j)
			newenvp[i] = ft_strdup(envp[i]);
		else
			newenvp[i] = ft_strdup(envp[i + 1]);
		i++;
	}
	newenvp[i] = NULL;
	//ft_free_array(envp);
	get_bash()->env = newenvp;
}

void	ft_unset(t_cmd_node *cmd_node, char **envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (cmd_node->cmd[i] != NULL)
	{

		len = ft_strlen(cmd_node->cmd[i]);
		while (envp[j] != NULL)
		{
			if (ft_strncmp(envp[j], cmd_node->cmd[i], len) == 0 && ((envp[j][len] == '=') || envp[j][len] == '\0'))
				ft_unset_var(envp, j);
			j++;
		}
		j = 0;
		i++;
	}
	get_exit_codes()->last_exit_code = 0;
}
