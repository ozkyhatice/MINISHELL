/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:39 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/30 23:09:09 by relvan           ###   ########.fr       */
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
	t_parse_node	*tmp;
	t_parse_node	*prev;

	tmp = shell->parse_head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->word == NULL)
		{
			if (prev)
				prev->next = tmp->next;
			else
				shell->parse_head = tmp->next;
			if (shell->parse_head == NULL)
			{
				shell->er_status = 1;
				shell->ex_status = 0;
				return ;
			}
			free(tmp);
			tmp = prev;
		}
		tmp = get_next_node(tmp, &prev);
	}
}

void	ft_parse(t_shell *shell)
{
	split_dollar(shell);
	tilda_control(shell);
	quote_remove(shell);
	delete_null_nodes(shell);
}

void	ft_execpre(t_shell *shell)
{
	counter_pipe(shell);
	put_cmnds(shell);
	add_indx_to_exnd(shell->exec_head);
	ft_redirection(shell);
}

void	start_program(t_shell *shell)
{
	while (shell->er_status != 2)
	{
		shell_readline(shell);
		if (shell->er_status == 0)
		{
			split_quote(shell);
			shell->er_status = syntax_rules(shell);
			if (shell->er_status != 0)
				shell->ex_status = 258;
			shell->l_br = 0;
			shell->r_br = 0;
		}
		if (shell->er_status == 0)
			ft_parse(shell);
		if (shell->er_status == 0)
			ft_execpre(shell);
		if (shell->er_status == 0)
			exec_handler(shell);
		if (shell->er_status != 2)
		{
			if (ft_strlen(shell->cmd_line) != 0)
				free(shell->cmd_line);
		}
		ft_freeallnodes(shell);
		if (shell->fd)
		{
			ft_free_intarr(shell->fd, shell);
			shell->fd = NULL;
		}
	}
}
