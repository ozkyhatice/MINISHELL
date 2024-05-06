#include "../include/minishell.h"

int ft_strtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(ft_istoken(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	split_char(t_shell *shell, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if(!str)
		return (0);
	if (ft_strtoken(str))
		return (1);
	while (str[i])
	{
		j = i;
		if (ft_istoken(str[i]))
			while(str[i] && str[i] == str[j])
				i++;
		else 
		{
			i = split_tokens(str, i);
		}		
		add_parse_node(shell, ft_substr(str, j, i - j));
	}
	return (0);
}

int	split_tokens(char *str, int i)
{
	char	q;

	while (str[i] && !ft_istoken(str[i]))
	{
		if (ft_isquote(str[i]))
		{
			q = str[i];
			i = i + 1;
			while (str[i] && str[i] != q)
				i = i + 1;
		}
		i = i + 1;
	}
	return (i);
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
		{
			add_parse_node(shell, str);
		}
		//print_parse_node(shell);
		free(str);
	}
}
