/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:35:10 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/22 14:52:40 by abkiraz          ###   ########.fr       */
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
