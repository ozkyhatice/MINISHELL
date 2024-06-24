/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:25:55 by abkiraz           #+#    #+#             */
/*   Updated: 2024/05/14 14:53:58 by abkiraz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	int			num;

	num = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			num = num * 10 + (*str - 48);
			str++;
		}
		else
			break ;
	}
	return (sign * num);
}
