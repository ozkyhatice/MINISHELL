/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:10 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:11 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	return (0);
}

void	builtin_run(t_exec_node *ex, t_shell *shell)
{
	if (ft_strncmp(ex->cmd[0], "echo", 5) == 0)
		run_echo(ex, shell);
	else if (ft_strncmp(ex->cmd[0], "pwd", 4) == 0)
		run_pwd();
	else if (ft_strncmp(ex->cmd[0], "env", 4) == 0)
		run_env(shell);
	else if (ft_strncmp(ex->cmd[0], "unset", 6) == 0)
		run_unset(shell);
	else if (ft_strncmp(ex->cmd[0], "export", 7) == 0)
		run_export(ex, shell);
	else if (ft_strncmp(ex->cmd[0], "exit", 5) == 0)
		run_exit(shell, ex->cmd[1], ex->cmd[2]);
	else if (ft_strncmp(ex->cmd[0], "cd", 3) == 0)
		run_cd(shell, ex);
}
