#include "../include/minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

int	ft_isquote(char c)
{
	return ((c == 34) || (c == 39));
}

int ft_istoken(char c)
{
	if (c == '|')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	else
		return (0);
}