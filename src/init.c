/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:39 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 16:53:04 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	// printwelcome();
	start_program(shell);
	ft_free_arr(shell->path);
	shell->path = NULL;
	ft_free_arr(shell->env_p);
	shell->env_p = NULL;
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
		// free(shell->cmd_line); double free olabilir
		return ;
	}
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

void	delete_null_nodes(t_shell *shell)
{
	t_parse_node	*tmp;
	t_parse_node	*prev;

	tmp = shell->parse_head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->word == NULL)
		{
			if (prev)
				prev->next = tmp->next;
			else
				shell->parse_head = tmp->next;
			if (shell->parse_head == NULL)
			{
				shell->er_status = 1;
				shell->ex_status = 0;
				return ;
			}
			free(tmp);
			tmp = prev;
		}
		prev = tmp;
		if (tmp)
			tmp = tmp->next;
	}
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
		{
			split_dollar(shell);
			tilda_control(shell);
			quote_remove(shell);
			// print_parse_node(shell);
			delete_null_nodes(shell);
			// print_parse_node(shell);
		}
		if (shell->er_status == 0)
		{
			counter_pipe(shell);
			put_cmnds(shell);
			add_indx_to_exnd(shell->exec_head);
			ft_redirection(shell);
		}
		if (shell->er_status == 0)
		{
			exec_handler(shell);
		}
		if (shell->er_status != 2)
		{
			if (ft_strlen(shell->cmd_line) != 0)
				free(shell->cmd_line);
		}
		ft_free_nodes(shell);
		ft_free_execnodes(shell);
	}
}
