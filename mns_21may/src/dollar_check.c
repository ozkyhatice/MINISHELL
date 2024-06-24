#include "../include/minishell.h"

void	dollar_nullcontrol(t_shell *shell, char *str)
{
	char	*tmp;

	tmp = ft_substr(str, 1, ft_strlen(str) - 1);
	add_parse_subnode(shell, tmp);
	free(tmp);
}


int	dollar_control(char c)
{
	if (c == '%' || c == '+' || c == ',' || c == '.' || c == '/'
		|| c == ':' || c == '=' || c == ']' || c == '^' || c == '}'
		|| c == '~' || c == ' ')
	{
		return (1);
	}
	if (c == '\0' || ft_isquote(c))
		return (1);
	return (0);
}