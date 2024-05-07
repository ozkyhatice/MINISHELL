/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:47:16 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/24 16:08:17 by abkiraz          ###   ########.fr       */
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
