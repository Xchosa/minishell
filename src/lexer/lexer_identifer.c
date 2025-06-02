

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



// leider komplett falsch
// besser:
// tokens vor dem splitten durch gehen 
// bool export_case(char *line)
// {
// 	if(ft_strncmp("export", line, 6) == 0)
// 		line += 6;
// 	else
// 		return (true);
// 	while(line)
// 	{
// 		skip_whitespace(&line);
// 		if (ft_isalpha(*line) != true)
// 			return (false);
// 		line++;
// 		while(*line && ft_strncmp("=", line, 1) != 0 )
// 		{
// 			if(ft_isalnum(*line) != true)
// 				return(false);
// 			line++;
// 		}
// 		line++;// / sind nach dem g= 
// 		if(ft_strncmp("\"", line, 1) != 0)
// 			{
// 				if(d_quote_case_no_div(line) != true)// nimmt alles ausser devider
// 					return(false);
// 			}
// 		if(only_one_cmd(line) != true) // nimmt nur erstes wort , fur tokeniser
// 			return(false);// abwegen was im export tokeniser gemacht werden sollte
// 	}
// 	return(true);
// }
