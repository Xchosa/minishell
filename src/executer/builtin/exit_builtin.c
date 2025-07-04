
#include "executer.h"

int	ft_isnum(char *s)
{
	int	i;

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
				ft_putendl_fd("shell: exit: too many arguments\n", 2);
				get_exit_codes()->last_exit_code = 1;
				return ;
			}
		}
		else
		{
			ft_putendl_fd("shell: exit: numeric argument required", 2);
			get_exit_codes()->last_exit_code = 255;
			exit(255);
		}
	}
	get_exit_codes()->last_exit_code = re;
	exit(re);
}
