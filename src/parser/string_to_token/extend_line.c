


#include "parser.h"


// fuer $USER -> 'testcase' reinschreiben
// letzter schritt erst mit env abgleichen 
char *extend_line(char **line)
{
    // char **line_start;
    char *new_line;
    char *tmp_line;

	new_line = ft_strdup("");
	while(**line != '\0')
    {
		// line_start = line;
		if(**line != '\0' && ft_strchr("\"", **line) != NULL)
		{
			while(**line != '\0' || ft_strchr("\"", **line) != NULL) 
			{
				// (*line)++;
				if (ft_strchr("$", **line) != NULL) // wenn $ auftaucht 
				{
					(*line)++;
					char *env_str;
					// $USER wird zu env_str = USER und dann zu poverbec
					env_str = get_env_in_line(line);
					while((*env_str) != '\0')
					{
						tmp_line = ft_charjoin(new_line, (*env_str));
						if (!tmp_line)
							return (NULL);
						new_line = tmp_line;
						env_str++;
					}
					(*line)++;
					break ;
				}

				else
					(*line)++;
			}
		}
		while(**line != '\0' && ft_strchr("\'", **line) != NULL)
		{
			while(**line != '\0' || (ft_strchr("\"", **line) != NULL))
			{
				if(ft_strchr("\'", *line[1]) != NULL)
				{
					**line +=2;
					break;
				}
				(*line)++;
			}

		}
		if(ft_strchr("$", **line) != NULL) 
		{
			(*line)++;
			// erstmal in new_line testcase fuer &USER reinschreiben 
			//// alles bis '" oder space in env suchen und auflosen 
		}
		else if (**line != '\0')
		{
			tmp_line= ft_charjoin(new_line, (**line));
			if (!tmp_line)
				return (NULL);
			new_line = tmp_line;
			(*line)++;
		}
	}
	return(new_line);
}



char *get_env_in_line( char **line)
{
	char *tmp_line;
	char *env_str;
	char *return_str;
	// t_bash *bash_env;

	// bash_env = get_bash()->env
	env_str = ft_strdup("");
	// (*line)++; // pass the dollar 
	if(!(*line))
		return(env_str);
	while(**line != '\0' && ft_strchr("\"\' ", (**line)) == NULL)
	{
		tmp_line = ft_charjoin(env_str, (**line));
        if (!tmp_line)
        	return (env_str = ft_strdup(""));
        env_str = tmp_line;
		(*line)++;

	
	}
	if(!(*env_str))
		return(env_str);
	return_str = get_var_from_env(get_bash()->env, env_str);
	// env_str in bash->env suchen 
	return(return_str);
}
