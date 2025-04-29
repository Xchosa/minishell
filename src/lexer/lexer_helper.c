

#include "parser.h"
#include "minishell.h"

static bool correct_out_direction(char *line)
{
    int i;

    i = 0;
    if (ft_strncmp (">", &line[i +1], 1) == 0)
        {
            if(check_for_divider_without_space(line[i+2]) == true)
                return(false);
            return(true);
        }
        if ((ft_strncmp ("<", &line[i +1], 1) == 0))
            return (false);
    return true;
}


bool	check_for_correct_double_divider(char *line)
{
    int i;

    i = 0;
	if (ft_strncmp ("<", &line[i], 1) == 0)
    {
        if (ft_strncmp ("<", &line[i +1], 1) == 0)
		{
            if(check_for_divider_without_space(line[i+2]) == true)
                return(false);
            return(true);
        }
        if ((ft_strncmp (">", &line[i +1], 1) == 0))
            return (false);
    }
	if (ft_strncmp (">", &line[i], 1) == 0)
    {
        if(correct_out_direction(line) == false)
            return(false);
    }
	return (true);
}

bool    check_for_correct_single_divider(char *line)
{
    int i;

    i = 0;
    if (ft_strncmp ("|", &line[i], 1) == 0)
    {   
        if (ft_strncmp ("|", &line[i +1], 1) == 0)
            return (false);
        if (ft_strncmp (";", &line[i +1], 1) == 0)
            return (false);
        if (line[i +1] == '\0')
            return (false);
    }
    if ((ft_strncmp (";", &line[i +1], 1) == 0))
    {
        if (ft_strncmp ("|", &line[i +1], 1) == 0)
            return (false);
        if (ft_strncmp (";", &line[i +1], 1) == 0)
            return (false);
        if (line[i +1] == '\0')
            return (false);
    }
    return(true);
}
bool	wrong_use_pipe_and_redirection(char *line)
{
	int i;
	int size;
	
	i = 0;
	if ((line[i] == '|')|| (line[i] == '<') || (line[i] == '>') || (line[i] == ';'))
		return (false);
	size = ft_strlen(line);
	if (line [size -1] == '|')
		return (false);
	return(true);
}