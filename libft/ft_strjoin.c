/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:59:44 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/23 01:59:49 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		*(str + i) = *((char *)(s1 + i));
		i++;
	}
	while (*(s2 + j))
	{
		*(str + i + j) = *((char *)(s2 + j));
		j++;
	}
	*(str + i + j) = '\0';
	return (str);
}
