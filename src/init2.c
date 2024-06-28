/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:12:40 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/28 18:15:08 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_freeallnodes(t_shell *shell)
{
	ft_free_nodes(shell);
	ft_free_execnodes(shell);
}

char	**copyenv(char **env)
{
	char	**return_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	return_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		return_env[i] = ft_strdup(env[i]);
	return_env[i] = NULL;
	return (return_env);
}

void	initalizer(t_shell *shell, char **env)
{
	env_init(shell, env);
	shell->env_p = copyenv(env);
	shell->std_out = 1;
	start_program(shell);
	ft_free_arr(shell->path);
	shell->path = NULL;
	ft_free_arr(shell->env_p);
	shell->env_p = NULL;
}

void	shell_readline2(t_shell *shell)
{
	if (ft_strcmp(shell->cmd_line, ""))
	{
		add_history(shell->cmd_line);
		shell->er_status = 0;
	}
	else
		free(shell->cmd_line);
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
		return ;
	}
	shell_readline2(shell);
}
