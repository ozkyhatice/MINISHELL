/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:22 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:23 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_exit_msg(char *str, char *str2)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(str2, 2);
}

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
		ft_putstr_fd("exit\n", 2);
		exit(shell->ex_status);
	}
	else if (ft_is_all_alpha(str))
	{
		ft_error_exit_msg(str, " numeric argument required");
		exit(255);
	}
	else if (s2)
	{
		ft_error_exit_msg(str, " too many arguments");
		exit(1);
	}
	else if (ft_is_all_digit(str) || ft_atoi(str) != 0)
	{
		code = get_exit_code(str);
		printf("exit\n");
		exit(code);
	}
}
