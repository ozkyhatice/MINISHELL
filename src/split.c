#include "../include/minishell.h"

int ft_strtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(ft_istoken(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	split_char(t_shell *shell, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if(!str)
		return (0);
	if (!ft_strtoken(str))
		return (1);
	while (str[i])
	{
		j = 0;
		if (ft_istoken(str[i]))
			while(str[i] && str[i] == str[j])
				i++;
		else 
			return 0;
		add_parse_node(shell, ft_substr(str, j, i - j));
	}
	return (0);
}

void	split_quote(t_shell *shell)
{

	int	i;
	int	first;
	int	quote;
	char *str;

	i = 0;
	while(shell->cmd_line && shell->cmd_line[i])
	{
		while (shell->cmd_line[i] && ft_isspace(shell->cmd_line[i]))
			i++;
		first = i;
		while (shell->cmd_line[i] && !ft_isspace(shell->cmd_line[i]))
		{
			if (ft_isquote(shell->cmd_line[i]))
			{
					quote = shell->cmd_line[i];
				i++;
				while (shell->cmd_line[i] && shell->cmd_line[i] != quote)
					i++;
			}
			i++;
		}
		str = ft_substr(shell->cmd_line, first, i - first + 1);
		if (split_char(shell, str))
			add_parse_node(shell, str);
		free(str);
	}
}
