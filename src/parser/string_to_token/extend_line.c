


#include "parser.h"


// fuer $USER -> 'testcase' reinschreiben
// letzter schritt erst mit env abgleichen 
char *extend_line(char **line)
{
    char *new_line;
    char *tmp_line;
	char *original_line;

	original_line = (*line);
	tmp_line = NULL;
	new_line = ft_strdup("");
	while(**line != '\0')
    {
		if(**line != '\0' && ft_strchr("\"", **line) != NULL)
		{
			new_line = add_single_char_to_line(new_line, tmp_line, line);
			while(**line != '\0' && ft_strchr("\"", **line) == NULL) 
				new_line = d_qoutes_swap_dollar_var_with_env_var(new_line, tmp_line, line);
		}
		if(**line != '\0' && ft_strchr("\'", **line) != NULL)
			new_line = add_s_quotes_str_to_line(new_line, tmp_line, line);
		if(**line != '\0' && ft_strchr("$", **line) != NULL) 
			new_line = swap_dollar_var_with_env_var(new_line, tmp_line, line);
		else if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
	}
	free(original_line);
	return(new_line);
}


//get_env_in_line iterates line up until a $var is done 
char *d_qoutes_swap_dollar_var_with_env_var(char *new_line, char *tmp_line, char **line)
{
	char *env_str;
	if (ft_strncmp("$?", (*line), 2) == 0)
		new_line = swap_exit_code_in_line(new_line, tmp_line, line);
	else if (ft_strchr("$", **line) != NULL) // wenn $ auftaucht 
	{
		(*line)++;
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
		return (new_line);
	}
	else if (**line != '\0')
	{
		new_line = add_single_char_to_line(new_line, tmp_line, line);
	}
	if (ft_strchr("\"", (**line)) != NULL)
		new_line = add_single_char_to_line(new_line, tmp_line, line);
	return (new_line);
}


char *add_s_quotes_str_to_line(char *new_line, char *tmp_line, char **line)
{
	if(**line != '\0' && ft_strchr("\'", **line) != NULL)
	{
		if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		while (**line != '\0' && ft_strchr("\'", (**line)) == NULL)
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		if (**line != '\0')
			new_line = add_single_char_to_line(new_line, tmp_line, line);
		return (new_line);
	}
	return (new_line);
}


char *swap_dollar_var_with_env_var(char *new_line, char *tmp_line, char **line)
{
	char *env_str;
	if (ft_strncmp("$?", (*line), 2) == 0)
		new_line = swap_exit_code_in_line(new_line, tmp_line, line);
	else if (ft_strchr("$", **line) != NULL)
	{
		(*line)++;
		env_str = get_env_in_line(line);
		while((*env_str) != '\0')
		{
			tmp_line = ft_charjoin(new_line, (*env_str));
			if (!tmp_line)
				return (NULL);
			new_line = tmp_line;
			env_str++;
		}
		// free env?
		return (new_line);
	}
	return(new_line);
}

char *swap_exit_code_in_line(char *new_line, char *tmp_line, char **line)
{
	char *exit_code;
	char *start_exit_code;

	(*line) +=2;
	exit_code = (ft_itoa(get_exit_codes()->last_exit_code));
	start_exit_code = exit_code;
	while((*exit_code) != '\0')
	{
		tmp_line = ft_charjoin(new_line, (*exit_code));
		if (!tmp_line)
			return (NULL);
		new_line = tmp_line;
		exit_code++;
	}
	free(start_exit_code);
	return (new_line);
}
