/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:45:07 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 14:59:25 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			if (ex_redir->type == OUTPUT)
				ft_red_great(ex, ex_redir, shell);
			else if (ex_redir->type == APPENDOUT)
				ft_red_dgreat(ex, ex_redir, shell);
			else if (ex_redir->type == INPUT)
				ft_red_less(ex, ex_redir, shell);
			else if (ex_redir->type == HD)
				ft_redir_dless(ex, ex_redir, shell);
			if (shell->ex_status == 1)
			{
				if (ex->next)
					shell->ex_status = 0;
				ex->ex_flag = 0;
			}
			ex_redir = ex_redir->next;
		}
		ex = ex->next;
	}
}
