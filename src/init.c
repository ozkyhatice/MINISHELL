/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:29 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:30 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	node_control(t_shell *shell)
{
	t_parse_node	*tmp;

	tmp = shell->parse_head;
	while (tmp)
	{
		if (tmp->word != NULL)
			return ;
		tmp = tmp->next;
	}
	shell->er_status = 1;
}

void	pipe_control(t_shell *shell)
{
	t_parse_node	*tmp;
	t_parse_node	*tmp2;

	tmp = shell->parse_head;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next == NULL)
			shell->er_status = 1;
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			tmp2 = tmp;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			tmp = tmp->next;
			free(tmp2);
		}
		else
			tmp = tmp->next;
	}
}

void	start_control(t_shell *shell)
{
	if (shell->er_status == 0)
		ft_parse(shell);
	if (shell->er_status == 0)
		ft_execpre(shell);
	if (shell->er_status == 0)
		exec_handler(shell);
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
		start_control(shell);
		if (shell->er_status != 2)
		{
			if (ft_strlen(shell->cmd_line) != 0 && !(*shell->cmd_line == '\0'))
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
