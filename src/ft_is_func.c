/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:32 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:33 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

int	ft_isquote(char c)
{
	return ((c == 34) || (c == 39));
}

int	ft_istoken(char c)
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

int	ft_exist(char *str, char c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i++] == c)
				return (1);
		}
	}
	return (0);
}

int	ft_is_all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
