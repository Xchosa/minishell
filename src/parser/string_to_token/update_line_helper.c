#include "parser.h"
#include "minishell.h"


char	*update_line_unitl_d_quotes(char *line)
{
	line++;
	while(ft_strncmp( "\"", line, 1) != 0)
 		line++;
	line++;
	return (line);
}

char	*update_line_unitl_s_quotes(char *line)
{
	line++;
	while(ft_strncmp( "\'", line, 1) != 0)
		line++;
	line++;
	return (line);
}

char	*update_line_until_space(char *line)
{
	line++;
    while (*line && ft_strncmp(" ", line, 1) != 0)
    {
        line++;
    }
    return (line);
}

char *handle_special_characters(char *line)
{
    if (ft_strncmp("\"", line, 1) == 0)
        return (update_line_unitl_d_quotes(line));
    if (ft_strncmp("\'", line, 1) == 0)
        return (update_line_unitl_s_quotes(line));
    if (ft_strncmp("$", line, 1) == 0)
        return (update_line_until_space(line));
    if (ft_strncmp("=", line, 1) == 0)
        return (++line); 
    return (NULL); 
}
