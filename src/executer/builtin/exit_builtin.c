
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
			//cleanfunktion
			exit(255);
		}
	}
	get_exit_codes()->last_exit_code = re;
	//clean funktion
	exit(re);
}


// You will also need to modify your exit builtin to stop calling exit() 
// directly and your ft_execute function to return the appropriate status.
//  This change ensures that your shell's main loop remains in control of the program's 
//  lifecycle and can perform all necessary cleanup before shutting down.

//cmd list hier freen? oder command list doch ausserhalb vom execute loop freen?