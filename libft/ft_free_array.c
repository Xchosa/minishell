

#include "./libft.h"


/*
frees a 2D array
*/
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
