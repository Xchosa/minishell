

#include "parser.h"
#include "minishell.h"


char** ft_cpy_array_str(char **arrays)
{
    char **new_array;
    int i;
    
    if (!arrays)
        return (NULL);
    while (arrays[i] != NULL)
        i++;
    new_array = (char**)malloc((i + 1) * sizeof(char*));
    if (!new_array)
        return (NULL);
    
    i = 0;
    while (arrays[i] != NULL)
    {
        new_array[i] = ft_strdup(arrays[i]);
        i++;
    }
    new_array[i] = NULL;
    return (new_array);
}

void ft_free_array(char **arrays)
{
    int i;

    i = 0;
    while(arrays[i])
        i++;
    while(i >= 0)
    {
        free(arrays[i]);
        i--;
    }
    free(arrays);
}

char **cpy_token_char(char *token)
{
    char **cmd_array;

    int i;

    i = 0;
    cmd_array = (char**)malloc(2 *sizeof(char*));

    cmd_array[i++] = ft_strdup(token);
    cmd_array[i] = NULL;
    return (cmd_array);
}


// copy another string to the array of strings. Last string is null. 


void append_token_char(t_cmd_node *cmd_node, t_token *curr_token)
{
    char **append_cmd_array;
    int i;
    int len;

    i = 0;
    while (cmd_node->cmd[i] != NULL)
        i++;
    len = i;
    append_cmd_array= (char**)malloc((len + 2)*sizeof(char*));
    if(!append_cmd_array)
        return;
    i = 0;
    while(i < len)
    {
        append_cmd_array[i] = ft_strdup(cmd_node->cmd[i]);
        i++;
    }
    append_cmd_array[i]= ft_strdup(curr_token->token);

    append_cmd_array[i+1]= NULL;
    
    ft_free_array(cmd_node->cmd);
    cmd_node->cmd = append_cmd_array;\
    // i = 0;
    // printf("cmd node cmd array:\n");
    // while(cmd_node->cmd[i] != NULL)
    // {
    //     printf("cmd node %s\n", cmd_node->cmd[i]);
    //     i++;
    // }
}
