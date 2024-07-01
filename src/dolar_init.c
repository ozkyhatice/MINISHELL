/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 04:40:22 by relvan            #+#    #+#             */
/*   Updated: 2024/07/01 04:40:43 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_dollar(t_shell *shell, char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (tmp)
	{
		add_parse_subnode(shell, tmp);
		free(tmp);
	}
}

void	add_dollar(t_shell *shell, char *str)
{
	char	*tmp;
	char	*dollar;
	char	*join;

	tmp = ft_strdup(str);
	dollar = ft_strdup("$");
	if (tmp)
	{
		join = ft_strjoin(dollar, tmp);
		add_parse_subnode(shell, join);
		free(tmp);
		free(dollar);
		free(join);
	}
}
