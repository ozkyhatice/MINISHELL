/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:25 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:26 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shell_readline2(t_shell *shell)
{
	if (ft_is_all_space(shell->cmd_line) == 0 && ft_strlen(shell->cmd_line))
	{
		add_history(shell->cmd_line);
		shell->er_status = 0;
	}
	else if (ft_is_all_space(shell->cmd_line))
	{
		add_history(shell->cmd_line);
		shell->er_status = 1;
		return ;
	}
	else
	{
		shell->er_status = 1;
		return ;
	}
	if (check_missing_quotes(shell->cmd_line) != 0)
	{
		printf("bash: missing quotes error\n");
		shell->ex_status = 258;
		shell->er_status = 1;
	}
}

void	shell_readline(t_shell *shell)
{
	shell->cmd_line = readline("minishell ~ ");
	shell->ex_ex_status = shell->ex_status;
	shell->c_pipe = 0;
	shell->ex_status = 0;
	shell->er_status = 0;
	if (shell->cmd_line == NULL && g_sig != IN_HEREDOC)
	{
		printf("exit\n");
		shell->er_status = 2;
		exit(0);
	}
	else if (*shell->cmd_line == '\0')
	{
		shell->er_status = 1;
		shell->ex_status = 0;
		free(shell->cmd_line);
		return ;
	}
	shell_readline2(shell);
}
