/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:15 by abkiraz           #+#    #+#             */
/*   Updated: 2024/07/01 04:33:51 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_msg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	define_rtype(t_parse_node *node, t_exec_node *exnode)
{
	t_parse_node	*tmp;
	t_exec_node		*ex;

	tmp = node;
	ex = exnode;
	(void)ex;
	while (tmp)
	{
		if (tmp->type == R_REDIR)
			tmp->next->type = OUTPUT;
		else if (tmp->type == APPEND)
			tmp->next->type = APPENDOUT;
		else if (tmp->type == L_REDIR)
			tmp->next->type = INPUT;
		else if (tmp->type == HEREDOC)
			tmp->next->type = HD;
		tmp = tmp->next;
	}
}
