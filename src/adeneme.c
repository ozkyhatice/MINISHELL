/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adeneme.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:54 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/29 16:29:22 by akdemir          ###   ########.fr       */
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
		if (local->tmp->type == WORD)
			local->cmnds->cmd[local->i++] = ft_strdup(local->tmp->word);
		local->j++;
		local->tmp = local->tmp->next;
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
		if (local.head != NULL)
			local.head = local.head->next;
		local.tmp = get_parse_node(shell->parse_head, local.j);
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
}
