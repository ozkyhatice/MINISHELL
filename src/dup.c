/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:57 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:58 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_indx_to_exnd(t_exec_node *exnd)
{
	int	i;

	i = 0;
	while (exnd)
	{
		exnd->id = i;
		i++;
		exnd = exnd->next;
	}
}

void	wait_all(t_exec_node *exnd)
{
	int	status;

	while (exnd)
	{
		waitpid(exnd->pid, &status, 0);
		exnd = exnd->next;
	}
}

void	wait_al(t_shell *shell)
{
	t_exec_node	*ex;
	int			status;
	int			i;
	t_exec_node	*cmd;

	i = 0;
	ex = shell->exec_head;
	while (ex)
	{
		waitpid(ex->pid, &status, 0);
		ex = ex->next;
		i++;
	}
	cmd = get_exec_node(shell->exec_head, i - 1);
	if (is_builtin(cmd->cmd[0]) != 1)
	{
		if (WIFEXITED(status))
			shell->ex_status = WEXITSTATUS(status);
	}
}

void	set_dup2(t_shell *shell, int i)
{
	if (shell->redir_flag)
	{
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
		dup2(shell->fd[i][1], STDOUT_FILENO);
	}
	else if (i == 0)
		dup2(shell->fd[i][1], STDOUT_FILENO);
	else if (i == shell->c_pipe - 1)
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
		dup2(shell->fd[i][1], STDOUT_FILENO);
	}
	fd_closer(shell);
}
