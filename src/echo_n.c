/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abuiltin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:08 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/28 20:51:12 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_n(char *keyword)
{
	int	i;

	i = 0;
	while (keyword[++i])
		if (keyword[i] != 'n')
			return (0);
	return (1);
}

int	is_full_space(char *rl)
{
	int	i;

	i = 0;
	while (rl && rl[i])
	{
		if (rl[i] != ' ' && rl[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
