/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:05 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:06 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (c == '%' || c == '+' || c == ',' || c == '.' || c == '/' || c == ':'
		|| c == '=' || c == ']' || c == '^' || c == '}' || c == '~' || c == ' ')
	{
		return (1);
	}
	if (c == '\0' || ft_isquote(c))
		return (1);
	return (0);
}

int	dollar_control2(char c, t_shell *shell, char *tmp)
{
	if (c == '(' || c == '[' || c == 92 || c == '{' || c == ')' || c == ';')
		return (1);
	else if (c == '#' || c == '-')
	{
		if (c == '-')
			add_parse_subnode(shell, "himBH");
		else if (c == '#')
			add_parse_subnode(shell, "0");
		add_parse_subnode(shell, (tmp + 1));
	}
	return (0);
}

int	special_dollar(char c)
{
	return (c == '0' || c == '?');
}
