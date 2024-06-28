/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:58 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 10:12:59 by abkiraz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fd(t_exec_node *exnd, int i, int count)
{
	t_exec_node	*ex;

	(void)i;
	(void)count;
	ex = exnd;
	while (ex->next)
	{
		if (ex->fd[0] != -1)
			close(ex->fd[0]);
		if (ex->fd[1] != -1)
			close(ex->fd[1]);
		ex = ex->next;
	}
}

void	open_fd(t_exec_node *exnd)
{
	t_exec_node	*ex;

	ex = exnd;
	while (ex->next)
	{
		pipe(ex->fd);
		ex = ex->next;
	}
}

void	open_pipes(t_shell *shell) // senem
{
	int **fd;
	int i;

	if (shell->c_pipe > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (shell->c_pipe - 1));
		i = -1;
		while (++i < shell->c_pipe - 1)
			fd[i] = malloc(sizeof(int) * 2);
		shell->fd = fd;
		i = -1;
		while (++i < shell->c_pipe - 1)
			pipe(shell->fd[i]);
	}
}

void	fd_closer(t_shell *shell) // senemdden
{
	int i;

	i = -1;
	while (++i < shell->c_pipe - 1)
	{
		if (shell->fd[i][1] != -1)
			close(shell->fd[i][1]);
		if (shell->fd[i][0] != -1)
			close(shell->fd[i][0]);
	}
}
