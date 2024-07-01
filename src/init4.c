/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 07:43:47 by relvan            #+#    #+#             */
/*   Updated: 2024/07/01 07:45:31 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parse_node	*get_next_node(t_parse_node *current, t_parse_node **prev)
{
	if (*prev)
		*prev = current;
	if (current)
		return (current->next);
	return (NULL);
}

void	delete_null_nodes(t_shell *shell)
{
	t_parse_node	*current;
	t_parse_node	*next;

	current = shell->parse_head;
	while (current != NULL)
	{
		next = current->next;
		if (current->word == NULL)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == shell->parse_head)
				shell->parse_head = current->next;
			if (current == shell->parse_tail)
				shell->parse_tail = current->prev;
			free(current->heredoc);
			free(current);
		}
		current = next;
	}
}

void	ft_parse(t_shell *shell)
{
	split_dollar(shell);
	tilda_control(shell);
	quote_remove(shell);
	delete_null_nodes(shell);
	node_control(shell);
}

void	ft_execpre(t_shell *shell)
{
	counter_pipe(shell);
	put_cmnds(shell);
	add_indx_to_exnd(shell->exec_head);
	ft_redirection(shell);
}
