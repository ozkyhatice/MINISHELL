/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:17 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 22:20:54 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_exec_node	*create_exec_node(void)
{
	t_exec_node	*new;

	new = malloc(sizeof(t_exec_node));
	if (new)
	{
		new->type = -1;
		new->cmd = NULL;
		new->heredoc = NULL;
		new->next = NULL;
		new->pid = -1;
		new->in = 0;
		new->out = 1;
		new->redirection_head = NULL;
		new->redirection_tail = NULL;
	}
	return (new);
}

void	add_exec_node(t_shell *shell)
{
	t_exec_node	*new;

	new = create_exec_node();
	if (shell->exec_head == NULL && new)
	{
		new->prev = NULL;
		shell->exec_head = new;
		shell->exec_tail = new;
	}
	else
	{
		new->prev = shell->exec_tail;
		shell->exec_tail->next = new;
		shell->exec_tail = new;
	}
}

void	print_exec_node(t_shell *shell)
{
	t_exec_node	*current;
	t_red		*redir;
	int			j;
	int			i;

	current = shell->exec_head;
	redir = current->redirection_head;
	j = 0;
	while (current != NULL)
	{
		i = 0;
		while (current->cmd[i] != NULL)
		{
			dprintf(2, "node#%d	komut#%s\n", j, current->cmd[i]);
			while (redir)
			{
				dprintf(2, "ex id%d--DOSYA ADI:%s", current->id, redir->name);
				redir = redir->next;
			}
			i++;
		}
		current = current->next;
		j++;
	}
}

void	ft_free_execnodes(t_shell *shell)
{
	t_exec_node	*current;
	t_exec_node	*next;

	current = shell->exec_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->heredoc);
		ft_free_arr(current->cmd);
		free(current);
		current = next;
	}
	shell->exec_head = NULL;
	shell->exec_tail = NULL;
}
