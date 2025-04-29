
#include "parser.h"
#include "minishell.h"



int count_up_strings(char *line)
{
	int i;

	i = 0;
	if (ft_strncmp("\"", &line[i], 1) == 0)
	{
		i++;
		while(ft_strncmp("\"", &line[i], 1) != 0)
		{
			if(line[i] == '\0')
				return(-1);
			i++;
		}
	}
	if (ft_strncmp("\'", &line[i], 1) == 0 && line[i])
	{
		i++;
		while(ft_strncmp("\'", &line[i], 1) != 0)
		{
			if(line[i] == '\0')
				return(-1);
			i++;
		}
	}
	return(i);
}
