/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:51:06 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:51:07 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s1, int c)
{
	char	*str;
	char	c1;

	c1 = (unsigned char)c;
	str = (char *)s1;
	while (*str != c1 && *str)
		str++;
	if (*str == c1)
		return (str);
	return (0);
}
