/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:34 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:35 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(t_env *envc, char *env_var)
{
	if (envc == NULL || envc->name == NULL || env_var == NULL)
		return (NULL);
	while (envc)
	{
		if (ft_strcmp(env_var, envc->name) == 0)
			return (envc->content);
		envc = envc->next;
	}
	return (NULL);
}
