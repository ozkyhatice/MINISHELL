/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:56:25 by abkiraz           #+#    #+#             */
/*   Updated: 2024/05/03 14:24:49 by abkiraz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char	*begin;

	begin = str;
	while (*begin)
	{
		begin++;
	}
	return (begin - str);
}
