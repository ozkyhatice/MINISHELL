/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:51:10 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:51:11 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*s1;

	i = ft_strlen(s) + 1;
	s1 = (char *)malloc(i);
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, s, i);
	return (s1);
}
