/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acreate_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:53 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 20:18:14 by akdemir          ###   ########.fr       */
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

void	add_redirection_node(t_shell *shell, char *str, int type)
{
	t_red	*new;

	new = create_redirection_node(str, type);
	if (shell->exec_head->redirection_head == NULL && new)
	{
		new->prev = NULL;
		shell->exec_head->redirection_head = new;
		shell->exec_head->redirection_tail = new;
	}
	else
	{
		new->prev = shell->exec_head->redirection_tail;
		shell->exec_head->redirection_tail->next = new;
		shell->exec_head->redirection_tail = new;
	}
}
