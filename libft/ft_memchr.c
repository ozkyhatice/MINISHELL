/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:50:24 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:50:25 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dst, int c, size_t n)
{
	unsigned char	c1;
	unsigned char	*str;

	c1 = (unsigned char)c;
	str = (unsigned char *)dst;
	while (n-- > 0)
	{
		if (*str == c1)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
