/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arun_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:05 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 19:45:37 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_is_all_alpha(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isalpha(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	get_exit_code(char *str)
{
	int	code;

	if (ft_atoi(str) == 100)
		code = 100;
	else if (ft_atoi(str) == -100)
		code = 156;
	else
		code = ft_atoi(str) % 256;
	return (code);
}

void	run_exit(t_shell *shell, char *str, char *s2)
{
	int	code;

	if (!str)
	{
		write(1, "exit\n", 5);
		exit(shell->ex_status);
	}
	else if (s2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(" too many arguments\n", 2);
		exit(1);
	}
	else if (ft_is_all_digit(str) || ft_atoi(str) != 0)
	{
		code = get_exit_code(str);
		exit(code);
	}
	else if (ft_is_all_alpha(str))
	{
		ft_putstr_fd(" numeric argument required", 2);
		exit(255);
	}
}
