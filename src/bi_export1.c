/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:06 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 20:17:02 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_export(t_shell *shell, char *arg)
{
	char	**splitted;

	splitted = ft_split(arg, '=');
	if (ft_check_syntax(splitted[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		shell->ex_status = 1;
		ft_free_arr(splitted);
		return ;
	}
	if (!splitted[1])
		add_environment(shell, splitted[0], "");
	else
		add_environment(shell, splitted[0], splitted[1]);
	ft_free_arr(splitted);
}

int	ft_check_syntax(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isname(str[i]))
			return (1);
		i++;
	}
	return (0);
}