/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:26 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:27 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_red(t_exec_node *ex, t_red *ex_redir, t_shell *shell)
{
	if (ex_redir->type == OUTPUT)
		ft_red_great(ex, ex_redir, shell);
	else if (ex_redir->type == APPENDOUT)
		ft_red_dgreat(ex, ex_redir, shell);
	else if (ex_redir->type == INPUT)
		ft_red_less(ex, ex_redir, shell);
	else if (ex_redir->type == HD)
		ft_redir_dless(ex, ex_redir, shell);
}

void	ft_redirection(t_shell *shell)
{
	t_exec_node	*ex;
	t_red		*ex_redir;

	ex = shell->exec_head;
	while (ex)
	{
		ex_redir = ex->redirection_head;
		while (ex_redir && shell->ex_status != 1)
		{
			ft_red(ex, ex_redir, shell);
			if (shell->ex_status == 1)
			{
				if (ex->next)
					shell->ex_status = 0;
				if (ex->ex_flag == 1)
					ex->ex_flag = 0;
			}
			ex_redir = ex_redir->next;
		}
		ex = ex->next;
	}
}
