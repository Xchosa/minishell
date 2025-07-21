#include "executer.h"
#include "signal_tp.h"

void	ft_increase_shlvl(char **envp)
{
	int		i;
	int		j;
	char	*newshlvl;
	char	*freeme;
	char	*buf;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("SHLVL=", envp[i], 6) == 0)
			break;
		i++;
	}
	if (envp[i] == NULL) //durchgelaufen und kein SHLVL in ENV gefunden
		get_bash()->env = ft_export_variable("SHLVL=1", envp); //check this for 
	else
	{
		freeme = envp[i];
		while (j++ < 6)
			envp[i]++;
		buf = ft_itoa(ft_atoi(envp[i]) + 1);
		if (buf == NULL)
			return ;
		newshlvl = ft_strjoin("SHLVL=", buf);
		if (newshlvl == NULL)
			return (free(buf));
		envp[i] = newshlvl;	
		return (free(freeme), free(buf));
	}
	//printf("%s\n", ft_itoa(ft_atoi(envp[i]) + 1));
}

// int	ft_ask_shlvl(char **envp)
// {
// 	int	i;
// 	int	re;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (strncmp("SHLVL=", envp[i], 6) == 0)
// 			break ;
// 		i++;
// 	}
// 	re = ft_atoi(&envp[i][6]);
// 	return (re);
//}

char	*get_command_pointer(char *command, char **envp)
{
	char	*pwd;
	int		i;
	char	*path;

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
		pwd++; //can break if PWD unset. important?
		i++;
	}
	command++;
	path = ft_strjoin(pwd, command);
	return (path);
}

// void	ft_minishell_nested(char **envp)
// {
// 	int		pid;
// 	char	*path_to_mini;
// 	int		status;

// 	if ((ft_ask_shlvl(envp)) >= 9) // diese 4 zeilen muessen noch in die main oder so 
// 	{
// 		ft_putendl_fd("Shell level is restricted to max 9", 2);
// 		return ;
// 	}
// 	path_to_mini = get_minishell_pointer(envp);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// some handler;
// 		execve(path_to_mini, (char *[]){"minishell", NULL}, envp);
// 		perror("shell: minishell"); //change exit code
// 	}
// 	free(path_to_mini);
// 	wait(&status);
// 	if (WIFEXITED(status))
// 	{
// 		get_exit_codes()->last_exit_code = WEXITSTATUS(status);
// 	}
// }

char	*ft_execute_local(char *command, char **envp)
{
	char *path;

	//ft_printf("do i get here\n");
	path = get_command_pointer(command, envp);
	//ft_printf("%s\n", path);
	if (access(path, X_OK) == 0)
		return (path);
	else 
		return (free (path), NULL);
}