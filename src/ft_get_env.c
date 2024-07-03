/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:49 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/03 01:04:21 by relvan           ###   ########.fr       */
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
