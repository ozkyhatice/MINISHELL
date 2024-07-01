/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:39 by abkiraz           #+#    #+#             */
/*   Updated: 2024/07/01 03:44:59 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_all_free(t_shell *shell)
{
	ft_freeallnodes(shell);
	ft_free_shellfd(shell);
}

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
			if (ft_strlen(shell->cmd_line) != 0 && !(*shell->cmd_line == '\0'))
				free(shell->cmd_line);
		}
		ft_all_free(shell);
	}
}
