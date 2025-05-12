
#include "minishell.h"
#include "parser.h"


bool	check_for_div_with_space_and_eq(char c)
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
	if (ft_strncmp ("=", &c, 1) == 0)
		return (true);
	return (false);
}

t_token *create_token_equal_as_div(char *content)
{
	t_token *new_token;
	
	new_token = malloc (sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->token  = get_token_equal_as_div(content);
	new_token->token_type = get_token_type(content);
	new_token->next = NULL;
	return (new_token);
	// tokenadd_back(get_config()->token_list, new_token);
}

char *get_token_equal_as_div(char *content)
{
	int i;
	char *new_token;
	char *tmp_token;
	
	i = 0;
	new_token =ft_strdup("");
	while (content[i] != '\0' && check_for_div_with_space_and_eq(content[i]) == false)
	{
		if (char_is_alpha_nbr_and_no_whitespace(content[i]))
		{	
			tmp_token = ft_charjoin(new_token, content[i]);
            free(new_token);
            new_token = tmp_token;
		}
		if (check_for_div_with_space_and_eq(content[i +1 ]) == true)// decide export or not
			return (new_token);
		i++;
	}
	while (check_for_divider_without_space(content[i]) == true)
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




