/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:51:49 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:51:50 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned char	c1;
	int				i;

	i = (int)ft_strlen(s);
	c1 = (unsigned char)c;
	str = (char *)s;
	while (str[i] != c1 && i > 0)
		i--;
	if (str[i] == c1)
		return (str + i);
	return (0);
}
