

#include "parser.h"


t_token	*validate_token_str(t_token **new_token)
{
	if (!new_token)
        return (NULL);
	if (!(*new_token))
        return (NULL);

    if (!(*new_token)->token)
    {
		free_single_token(new_token);
		return (NULL);
    }
    return ((*new_token));
}


int process_content_to_token(char **line, t_token *token)
{
    int i;
    char *tmp_token;
    
    i = 0;
	if ((*line)[i] == '\'')
		i++;
	else if ((*line)[i] == '\"')
		i++;
    while((*line)[i] && (*line)[i] != '\"' && (*line)[i] != '\'')
    {
        tmp_token = ft_charjoin(token->token, (*line)[i]);
        if(!tmp_token)
            return (-1);
            
        free(token->token);
        token->token = tmp_token;
        i++;
    }
    return (i);
}

void skip_quotes(char **line)
{
	int i;

	i = 0;
	if(((*line)[i] == '\"') && (((*line)[i +1 ] == '\"') || (*line)[i +1 ] == '\''))
	{
		while(*line && **line != '\0')
		{
			if(ft_strchr("\"\'" , **line) != NULL)
				(*line)++;
			else 
				break;
		}
		return;
	}
	if(((*line)[i] == '\'') && (((*line)[i +1 ] == '\"') || (*line)[i +1 ] == '\''))
	{
		while(*line && **line != '\0')
		{
			if(ft_strchr("\"\'" , **line) != NULL)
				(*line)++;
			else 
				break;
		}
		return;
	}
	skip_single_quotes(line);
}


void skip_single_quotes(char **line)
{
	int	i;

	i = 0;
	if(((*line)[i] == '\'') && ((*line)[i +1 ] == '\0'))
	{
		(*line)++;
		return;
	}
	if(((*line)[i] == '\"') && ((*line)[i +1 ] == '\0'))
	{
		(*line)++;
		return;
	}
}

