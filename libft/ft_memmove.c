/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:50:36 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:50:37 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	i = 0;
	dst1 = (char *)dst;
	src1 = (char *)src;
	if (!dst1 && !src1)
		return (0);
	if (dst1 > src1)
	{
		while (n--)
			dst1[n] = src1[n];
	}
	else
	{
		while (i < n)
		{
			dst1[i] = src1[i];
			i++;
		}
	}
	return (dst);
}
