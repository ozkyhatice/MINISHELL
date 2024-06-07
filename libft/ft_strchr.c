/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:07:10 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/22 14:43:55 by abkiraz          ###   ########.fr       */
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
