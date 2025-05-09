

#include "minishell.h"
#include "parser.h"

// handle case:     export    g4h="echo test"
// bash-3.2$     export    g4g=echo test
// bash-3.2$ echo $?
// 0
// bash-3.2$     export    4gh='echo test'
// bash: export: `4gh=echo test': not a valid identifier
// bash-3.2$     export    gh='echo test'
// bash-3.2$ echo $gh
// echo test
// bash-3.2$ echo $g4g
// echo

bool	d_quote_case_no_div(char *line)
{
	int i;

	i = 1;
	while(ft_strncmp("\"", line, 1) != 0)
	{
		if(line[i])
			return (false);
		if(check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
	i++;
	while(line[i])
	{
		skip_whitespace(&line);
		if (check_for_divider_without_space(line[i]) == true)
			return (false);
		i++;
	}
    return (true);

}


bool	only_one_cmd(char *line)
{
	int i;

	i = 1;
	// if(ft_strncmp(" ", line, 1) == 0)// falsch token sollte einfach leer sein
	// 	return(false);
	while(line[i])
	{
		if(check_for_divider_without_space(line[i]) == true)
			return (false);
		if(ft_strncmp(" ", line + i, 1) == true)
			break;
		i++;
	}
	// while(line[i])
	// {
	// 	if(check_for_divider_without_space(line[i]) == true)
	// 		return (false);
    //     i++;
	// }
    return(true);
}
// leider komplett falsch
bool export_case(char *line)
{
	if(ft_strncmp("export", line, 6) == 0)
		line += 6;
	else
		return (true);
	skip_whitespace(&line);
	if (ft_isalpha(*line) != true)
		return (false);
	line++;
	while(ft_strncmp("=", line, 1) != 0)
	{
		if(ft_isalnum(*line) != true)
			return(false);
		line++;
	}
	line++;// / sind nach dem g= 
	if(ft_strncmp("\"", line, 1) != 0)
		{
			if(d_quote_case_no_div(line) != true)// nimmt alles ausser devider
				return(false);
		}
	if(only_one_cmd(line) != true) // nimmt nur erstes wort , fur tokeniser
		return(false);// abwegen was im export tokeniser gemacht werden sollte
	return(true);
}

bool	lexer_valid_ident(char *line)
{
	int i;
	bool valid_ident;
	
	valid_ident = true;
	i = 0;
	{
		while(line[i])
		{
			skip_whitespace(&line);
			if(export_case(line+ i) == false)
			{
				get_exit_codes()->last_exit_code = invalid_identifier;
				return (valid_ident = false);
			}
			line++;
		}
	}
	return (valid_ident);
}