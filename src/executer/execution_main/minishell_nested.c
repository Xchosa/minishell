#include "executer.h"
#include "signal_tp.h"

void	ft_increase_shlvl(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("SHLVL=", envp[i], 6) == 0)
			envp[i][6]++;
		i++;
	}
}

int	ft_ask_shlvl(char **envp)
{
	int	i;
	int	re;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("SHLVL=", envp[i], 6) == 0)
			break ;
		i++;
	}
	re = ft_atoi(&envp[i][6]);
	return (re);
}

char	*get_minishell_pointer(char **envp)
{
	char	*pwd;
	int		i;
	char	*path_to_mini;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PWD", envp[i], 3) == 0)
		{
			pwd = envp[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pwd++;
		i++;
	}
	path_to_mini = ft_strjoin(pwd, "/minishell");
	return (path_to_mini);
}

void	ft_minishell_nested(char **envp)
{
	int		pid;
	char	*path_to_mini;
	int		status;

	if ((ft_ask_shlvl(envp)) >= 9) // diese 4 zeilen muessen noch in die main oder so 
	{
		ft_putendl_fd("Shell level is restricted to max 9", 2);
		return ;
	}
	path_to_mini = get_minishell_pointer(envp);
	ft_printf("%s\n", path_to_mini);
	pid = fork();
	if (pid == 0)
	{
		// some handler;
		execve(path_to_mini, (char *[]){"minishell", NULL}, envp);
		perror("shell: minishell"); //change exit code
	}
	free(path_to_mini);
	wait(&status);
	if (WIFEXITED(status))
	{
		get_exit_codes()->last_exit_code = WEXITSTATUS(status);
	}
}
