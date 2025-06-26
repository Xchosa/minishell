

#include "./libft.h"
/*
compares two strings and returns a boolean; 
true if they are identiacall. 
e.g. s1 = world s2= worldsee returns false 
*/
bool	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	if((s1[i] == '\0') && (s2[i] == '\0'))
		return (true);

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return((s1[i] == '\0') && (s2[i] == '\0'));
}
