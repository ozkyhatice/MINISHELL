/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:12:40 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 19:25:53 by relvan           ###   ########.fr       */
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

void free_env_list(t_env **head)
{
    t_env *current;
    t_env *next_node;

    current = *head;
    while (current)
    {
        next_node = current->next;
        free(current->name);
        free(current->content);
        free(current);
        current = next_node;
    }
    *head = NULL;
}

void	initalizer(t_shell *shell, char **env)
{
	env_p_init(shell, env);
	sort_env_list(&shell->env_p);
	env_init(shell, env);
	shell->std_out = 1;
	start_program(shell);
	ft_free_arr(shell->path);
	shell->path = NULL;
	free_env_list(&shell->env_p);
}
