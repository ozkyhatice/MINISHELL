/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:50:39 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:50:40 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (0 < len--)
	{
		*ptr = value;
		ptr++;
	}
	return (str);
}
