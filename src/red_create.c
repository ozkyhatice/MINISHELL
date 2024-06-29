/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:53 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/29 05:34:59 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_red	*create_redirection_node(char *str, int type)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (new)
	{
		new->type = type;
		new->name = ft_strdup(str);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}


void	add_redirection_node(t_exec_node *ex, char *str, int type)
{
	t_red	*new;

	new = create_redirection_node(str, type);
	if (ex->redirection_head == NULL && new)
	{
		new->prev = NULL;
		ex->redirection_head = new;
		ex->redirection_tail = new;
	}
	else
	{
		new->prev = ex->redirection_tail;
		ex->redirection_tail->next = new;
		ex->redirection_tail = new;
	}
}
