/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:30 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:31 by akdemir          ###   ########.fr       */
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

void	free_redirections(t_shell *shell)
{
	t_exec_node	*current_exec;
	t_red		*current_red;
	t_red		*next_red;

	current_exec = shell->exec_head;
	while (current_exec)
	{
		current_red = current_exec->redirection_head;
		while (current_red)
		{
			next_red = current_red->next;
			if (current_red->name)
				free(current_red->name);
			free(current_red);
			current_red = next_red;
		}
		current_exec->redirection_head = NULL;
		current_exec->redirection_tail = NULL;
		current_exec = current_exec->next;
	}
}
