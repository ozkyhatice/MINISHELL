/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:47 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:48 by akdemir          ###   ########.fr       */
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
