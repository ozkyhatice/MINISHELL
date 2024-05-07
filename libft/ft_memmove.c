/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:41:34 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/15 14:03:55 by abkiraz          ###   ########.fr       */
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
