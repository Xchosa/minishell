#include "minishell.h"
#include "parser.h"


char **extend_env_with_str(char** src, char *token)
{
    int i;
	int rows;
	char **cpy_env;

	rows = 0;
	while(src[rows] != NULL)
		rows++;
	cpy_env = (char **)malloc(sizeof(char*) * (rows + 2));
	i = 0;
    while(i < rows || src[i])
	{
		cpy_env[i] = ft_strdup(src[i]);
		i++;
	}
    cpy_env[i] = ft_strdup(token);
    printf("\nvariable found:\n %s \n", cpy_env[i]);
	cpy_env[i+1]= NULL;
	return(cpy_env);
}


// bool extend_env(t_token *token_lst)
// {
//     bool only_extend_env;
//     t_bash *new_bash;
//     t_bash *old_bash;
    
//     printf("bash issue?\n");
//     old_bash = get_bash();
//     new_bash = get_bash();
//     only_extend_env = false;
//     if(token_lst->head->token_type != EXPORT)
//         return (false);
//     while(token_lst != NULL && token_lst->next != NULL)
//     {
//         if(token_lst->token_type == Export_var)
//         {
//             token_lst = token_lst->next;
//             new_bash->env = extend_env_with_str(old_bash->env, token_lst->token);
//             //new_bash = get_bash();// somehow update static function 
//             only_extend_env = true;
//         }
//         else
//             token_lst = token_lst->next;
//     }
//     // ft_print_array(new_bash->env);
//     return  (only_extend_env);
// }
