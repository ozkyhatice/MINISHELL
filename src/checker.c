/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:10 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 13:43:02 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_missing_quotes(char *cmd_line)
{
	int	quote;
	int	i;

	quote = 0;
	i = -1;
	while (cmd_line[++i])
	{
		if (quote == 0 && (cmd_line[i] == 34 || cmd_line[i] == 39))
			quote = cmd_line[i];
		else if (quote == cmd_line[i])
			quote = 0;
	}
	return (quote);
}
