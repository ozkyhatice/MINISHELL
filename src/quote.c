/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:32 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:33 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_istoken(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	split_char(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*str2;

	i = 0;
	j = 0;
	if (!str && str[0] != '\0')
		return (0);
	if (ft_strtoken(str))
		return (1);
	while (str[i])
	{
		j = i;
		if (ft_istoken(str[i]))
			while (str[i] && str[i] == str[j])
				i++;
		else
		{
			i = split_tokens(str, i);
		}
		str2 = ft_substr(str, j, i - j);
		add_parse_node(shell, str2);
		free(str2);
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

void	split2_quote(t_shell *shell, int *first, int *i)
{
	int	quote;

	while (shell->cmd_line[*i] && ft_isspace(shell->cmd_line[*i]))
		(*i)++;
	*first = *i;
	while (shell->cmd_line[*i] && !ft_isspace(shell->cmd_line[*i]))
	{
		if (ft_isquote(shell->cmd_line[*i]))
		{
			quote = shell->cmd_line[*i];
			(*i)++;
			while (shell->cmd_line[*i] && shell->cmd_line[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

void	split_quote(t_shell *shell)
{
	int		i;
	int		first;
	char	*str;

	i = 0;
	while (shell->cmd_line && shell->cmd_line[i])
	{
		split2_quote(shell, &first, &i);
		str = ft_substr(shell->cmd_line, first, i - first);
		if (ft_strnstr(str, "$(", ft_strlen(str)))
			add_parse_node(shell, str);
		else if (split_char(shell, str))
			add_parse_node(shell, str);
		free(str);
	}
}
