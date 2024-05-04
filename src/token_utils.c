#include "../include/minishell.h"

int same_str(const char *str1, char *str2)
{
	int len1;
	int len2;
	int i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	i = 0;
	if(len1 != len2)
		return (0);
	while (i < len1)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}