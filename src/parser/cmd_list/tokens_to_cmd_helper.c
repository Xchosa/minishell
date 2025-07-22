


#include "parser.h"

void	check_cmd_builtin(t_cmd_node **cmd_node)
{
	if ((*cmd_node)->cmd_type == EXECUTE)
	{
		if((*cmd_node)->cmd[0] == NULL)
			return ;
		(*cmd_node)->cmd_type = correct_cmd_type(cmd_node);
	}
}

int	correct_cmd_type(t_cmd_node **cmd_node)
{
	int		cmd_type;
	char	*lower;

	cmd_type = 0;
	lower = ft_strtolower((*cmd_node)->cmd[0]);
    (*cmd_node)->cmd[0] = lower;
	cmd_type = (check_for_builtin(lower));
    if (cmd_type != 0)
		return (cmd_type);
	return (cmd_type = EXECUTE);
}


char	**ft_cpy_array_str(char **arrays)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!arrays)
		return (NULL);
	while (arrays[i] != NULL)
		i++;
	new_array = (char **)malloc((i + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (arrays[i] != NULL)
	{
		new_array[i] = ft_strdup(arrays[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	ft_free_array(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
		i++;
	while (i >= 0)
	{
		free(arrays[i]);
		i--;
	}
	free(arrays);
}

char	**cpy_token_char(char *token)
{
	char	**cmd_array;
	int		i;

	i = 0;
	cmd_array = (char **)malloc(2 * sizeof(char *));
	cmd_array[i++] = ft_strdup(token);
	cmd_array[i] = NULL;
	return (cmd_array);
}


