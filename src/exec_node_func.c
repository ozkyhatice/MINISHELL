/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:17 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/30 20:41:08 by relvan           ###   ########.fr       */
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
		new->in = -3;
		new->out = -3;
		new->ex_flag = 1;
		new->here_path = NULL;
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
			while (redir)
				redir = redir->next;
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
		if(current->here_path)
			free(current->here_path);
		if (current->cmd)
			ft_free_arr(current->cmd);
		free(current);
		current = next;
	}
	shell->exec_head = NULL;
	shell->exec_tail = NULL;
	if (shell->c_pipe > 1)
	{
		ft_free_intarr(shell->fd, shell);
		shell->fd = NULL;
	}
}
