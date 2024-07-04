/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:50:18 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:50:19 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenght(int nb)
{
	int	count;

	count = 0;
	if (nb <= 0)
		count++;
	while (nb != 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

	len = ft_lenght(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	if (nb == 0)
		str[0] = '0';
	while (nb != 0)
	{
		--len;
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
