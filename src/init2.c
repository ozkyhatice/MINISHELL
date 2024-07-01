/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:12:40 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/01 03:42:20 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_freeallnodes(t_shell *shell)
{
	ft_free_nodes(shell);
	free_redirections(shell);
	ft_free_execnodes(shell);
}

void	ft_free_shellfd(t_shell *shell)
{
	if (shell->fd)
	{
		ft_free_intarr(shell->fd, shell);
		shell->fd = NULL;
	}
}

void	delete_null_nodes(t_shell *shell)
{
	t_parse_node	*current;
	t_parse_node	*next;

	current = shell->parse_head;
	while (current != NULL)
	{
		next = current->next;
		if (current->word == NULL)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == shell->parse_head)
				shell->parse_head = current->next;
			if (current == shell->parse_tail)
				shell->parse_tail = current->prev;
			free(current->heredoc);
			free(current);
		}
		current = next;
	}
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
	shell->env = env;
	shell->env_p = copyenv(env);
	shell->std_out = 1;
	start_program(shell);
	ft_free_arr(shell->path);
	shell->path = NULL;
	ft_free_arr(shell->env_p);
	shell->env_p = NULL;
}
