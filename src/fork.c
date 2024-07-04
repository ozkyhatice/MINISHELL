/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:36 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:37 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_single_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	exnd = get_exec_node(shell->exec_head, i);
	path = getcmdpath(exnd->cmd[i], shell->path, shell->env_l);
	exnd = get_exec_node(shell->exec_head, i);
	set_io(exnd);
	if (execve(path, exnd->cmd, shell->env) == -1)
	{
		is_path_ok(path, exnd->cmd[0], &shell->ex_status);
		exit(shell->ex_status);
	}
}

void	ft_multi_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	g_sig = IN_CMD;
	set_dup2(shell, i);
	exnd = get_exec_node(shell->exec_head, i);
	set_io(exnd);
	if (is_builtin(exnd->cmd[0]))
	{
		builtin_run(exnd, shell);
		exit(shell->ex_status);
	}
	else
	{
		path = getcmdpath(exnd->cmd[0], shell->path, shell->env_l);
		if (execve(path, exnd->cmd, shell->env) == -1)
		{
			is_path_ok(path, exnd->cmd[0], &shell->ex_status);
			exit(shell->ex_status);
		}
	}
}

void	ft_ft_split(t_shell *shell)
{
	char		**tmp;
	char *const	path = ft_getenv(shell->env_l, "PATH");

	tmp = shell->path;
	if (path == NULL)
		shell->path = NULL;
	else
		shell->path = ft_split(path, ':');
	if ((tmp))
		free(tmp);
}

int	ft_execve(t_shell *shell, t_exec_node *ex, int i)
{
	if (shell->c_pipe == 1 && is_builtin(ex->cmd[0]))
		is_first_builtin(shell, ex);
	else
	{
		ex->pid = fork();
		if (ex->pid == 0)
		{
			if (ex->ex_flag == 0)
			{
				shell->ex_status = 1;
				exit (1);
			}
			ft_ft_split(shell);
			if (shell->c_pipe - 1 == 0)
				ft_single_exec(shell, i);
			else
			{
				ft_multi_exec(shell, i);
				return (1);
			}
		}
	}
	return (0);
}

int	exec_handler(t_shell *shell)
{
	int			i;
	t_exec_node	*exnd;

	i = 0;
	exnd = shell->exec_head;
	if (shell->exec_head->ex_flag == 3)
		return (1);
	g_sig = IN_CMD;
	if (shell->c_pipe > 1)
		open_pipes(shell);
	while (i < shell->c_pipe)
	{
		if (ft_execve(shell, exnd, i))
			exit(shell->ex_status);
		i++;
		exnd = exnd->next;
	}
	fd_closer(shell);
	wait_al(shell);
	g_sig = AFTER_CMD;
	return (0);
}
