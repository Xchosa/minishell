

#include "parser.h"
#include "minishell.h"

bool	check_for_export_divider(char c)
{
    if (ft_strncmp ("|", &c, 1) == 0)
		return (true);
	if (ft_strncmp (" ", &c, 1) == 0)
		return (true);
	if (ft_strncmp ("<", &c, 1) == 0)
		return (true);
	if (ft_strncmp (">", &c, 1) == 0)
		return (true);
	if (ft_strncmp (";", &c, 1) == 0)
		return (true);
    if (ft_strncmp ("\"", &c, 1) == 0)
		return (true);
	return (false);
}

char *handle_dividers_in_export(char *content)
{
    int i;
	char *new_token;
	char *tmp_token;

    i = 0;
	new_token =ft_strdup("");
    while (check_for_divider_without_space(content[i]) == true && content[i] != '\"')
    {
        tmp_token = ft_charjoin( new_token, content[i]);
	    free(new_token);
        new_token = tmp_token;
	    if(not_single_divider(content[i])== false )
		    return(new_token);
	    i++;
    }
    return(new_token);
}
// identisch nur das es bis "\" getokenised wird anstelle vom normalen
char* get_token_export_output(char *content)
{
    int i;
	char *new_token;
	char *tmp_token;

    i = 0;
	new_token =ft_strdup("");
    while (content[i] != '\"' && check_for_divider_with_space(content[i]) == false)
    {
        if (char_is_alpha_nbr_and_no_whitespace(content[i]))
		{	
			tmp_token = ft_charjoin(new_token, content[i]);
            free(new_token);
            new_token = tmp_token;
		}
        if (check_for_export_divider(content[i +1 ]) == true)
			return (new_token);
		i++;
    }
    tmp_token = handle_dividers_in_export(content);
    free(new_token);
    new_token = tmp_token;
    return(new_token);
}

bool check_divider_and_d_quotes_eof(char *line)
{
	int i;

	i = 0;
    if (*line == '\0')
        return (false);
    if (check_for_divider_with_space(line[i]) == true)
        return (false);
    if (ft_strncmp( "\"", line, 1) == 0)
        return (false);
    return (i);
}


char *update_export_output_line(char *line)
{
    bool flag;

	flag = false;
	skip_whitespace(&line);
    while (check_divider_and_d_quotes_eof(line) == true)
	{
		if(pipe_or_simec(*line)== true)
		{
			line++;
			return(line);
		}
		line++;
		flag = true;
	}
	if( flag == false || ft_strncmp( "\"", line, 1) != 0)
	{
		while (*line && (ft_isalnum(*line) || special_charcter_no_divider(*line)))
			line++;
	}
	return	(line);
}

// wenn export - dann token_lst in seperate static function
// erstmal seperate tokenliste laden
// soll ja erst aufgerufen werden wenn token mit spezifischen namen eigegeben wird sonst einfach eine /n ausdrucken 


// if cmd_node head = export - save cmd list in static function
t_token *create_token_export_output(char *line)
{
    t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token_export_output(line);
	new_token->token_type = get_token_type(line);
	new_token->next = NULL;
	return (new_token);
}