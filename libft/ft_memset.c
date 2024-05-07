/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:22:32 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/22 14:53:49 by abkiraz          ###   ########.fr       */
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
