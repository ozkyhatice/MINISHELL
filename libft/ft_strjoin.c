/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:51:19 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:51:20 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;

	if (!s1)
		lens1 = 0;
	else
		lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (lens2 + lens1 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, lens1 + 1);
	ft_strlcat(str, s2, lens1 + lens2 + 1);
	return (str);
}
