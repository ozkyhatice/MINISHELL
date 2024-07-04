/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:12 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:13 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	counter_pipe(t_shell *shell)
{
	t_parse_node	*node;

	shell->c_pipe = 0;
	node = shell->parse_head;
	while (node)
	{
		if (node->type == PIPE)
			shell->c_pipe++;
		node = node->next;
	}
	shell->c_pipe++;
	create_ex_nodes(shell);
}

void	create_ex_nodes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->c_pipe)
	{
		add_exec_node(shell);
		i++;
	}
}
