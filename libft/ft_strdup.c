/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:44:14 by abkiraz           #+#    #+#             */
/*   Updated: 2023/07/22 14:45:53 by abkiraz          ###   ########.fr       */
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
