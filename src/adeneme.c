/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adeneme.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:54 by abkiraz           #+#    #+#             */
/*   Updated: 2024/07/01 04:20:07 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	node_init(t_put_cmd *local)
{
	while (local->head && local->head->type != PIPE)
	{
		if (local->head->type == WORD)
			local->arg_len++;
		else if (local->head->type == INPUT || local->head->type == OUTPUT
			|| local->head->type == APPENDOUT || local->head->type == HD)
			add_redirection_node(local->cmnds, local->head->word,
				local->head->type);
		local->head = local->head->next;
	}
}

void	secondloop(t_put_cmd *local)
{
	while (local->i < local->arg_len)
	{
		if (local->tmp->type == WORD && local->tmp->word != NULL)
			local->cmnds->cmd[local->i++] = ft_strdup(local->tmp->word);
		local->j++;
		local->tmp = local->tmp->next;
	}
}

void	if_arg_len_zero(t_put_cmd local, t_shell *shell)
{
	if (local.arg_len == 0)
	{
		if (local.cmnds != NULL)
			local.cmnds->cmd = NULL;
		if (local.head != NULL)
			local.head = local.head->next;
		local.tmp = get_parse_node(shell->parse_head, local.j);
		local.cmnds->ex_flag = 3;
	}
}

void	ft_second_loop(t_put_cmd local)
{
	if (local.tmp != NULL && local.cmnds != NULL)
	{
		local.cmnds->cmd = malloc(sizeof(char *) * (local.arg_len + 1));
		if (!local.cmnds->cmd)
			return ;
		secondloop(&local);
		local.cmnds->cmd[local.i] = NULL;
		local.cmnds = local.cmnds->next;
	}
}

void	put_cmnds(t_shell *shell)
{
	t_put_cmd	local;

	define_rtype(shell->parse_head, shell->exec_head);
	local.head = shell->parse_head;
	local.cmnds = shell->exec_head;
	local.j = 0;
	while (local.head)
	{
		local.i = 0;
		local.arg_len = 0;
		node_init(&local);
		if (local.arg_len == 0)
		{
			if_arg_len_zero(local, shell);
			continue ;
		}
		if (local.head != NULL)
			local.head = local.head->next;
		local.tmp = get_parse_node(shell->parse_head, local.j);
		ft_second_loop(local);
	}
}
