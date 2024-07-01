/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 04:33:02 by relvan            #+#    #+#             */
/*   Updated: 2024/07/01 04:33:17 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_exec_node	*get_exec_node(t_exec_node *exnode, int indx)
{
	t_exec_node	*tmp;
	int			i;

	i = 0;
	tmp = exnode;
	while (tmp && i < indx)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == indx)
		return (tmp);
	return (NULL);
}

t_parse_node	*get_parse_node(t_parse_node *node, int indx)
{
	t_parse_node	*tmp;
	int				i;

	i = 0;
	tmp = node;
	while (tmp && i < indx)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == indx)
		return (tmp);
	return (NULL);
}
