/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:12 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:46:13 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	same_str(const char *str1, char *str2)
{
	int	len1;
	int	len2;
	int	i;

	if (!str1 || !str2)
		return (0);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	i = 0;
	if (len1 != len2)
		return (0);
	while (i < len1)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s2 == NULL)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
