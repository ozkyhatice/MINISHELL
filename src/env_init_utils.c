/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:50 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:51 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_copy(t_env *env)
{
	t_env	*new_list;
	t_env	*current;

	new_list = NULL;
	while (env)
	{
		current = env_listnew(ft_strdup(env->name), ft_strdup(env->content));
		if (!current)
		{
			while (new_list)
			{
				current = new_list->next;
				free(new_list->name);
				free(new_list->content);
				free(new_list);
				new_list = current;
			}
			return (NULL);
		}
		env_lstadd_back(&new_list, current);
		env = env->next;
	}
	return (new_list);
}

void	sort(char *tmp_name, char *tmp_content, t_env *current, t_env *next)
{
	tmp_name = current->name;
	tmp_content = current->content;
	current->name = next->name;
	current->content = next->content;
	next->name = tmp_name;
	next->content = tmp_content;
}

void	init_null(char **tmp_name, char **tmp_content)
{
	*tmp_name = NULL;
	*tmp_content = NULL;
}

void	env_sort(t_env **env)
{
	t_env	*current;
	t_env	*next;
	char	*tmp_name;
	char	*tmp_content;
	int		sorted;

	init_null(&tmp_name, &tmp_content);
	if (!env || !(*env))
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = *env;
		while (current->next)
		{
			next = current->next;
			if (ft_strcmp(current->name, next->name) > 0)
			{
				sort(tmp_name, tmp_content, current, next);
				sorted = 0;
			}
			current = next;
		}
	}
}

t_env	*env_sorted_copy(t_env *env)
{
	t_env	*sorted_copy;

	sorted_copy = env_copy(env);
	if (sorted_copy)
		env_sort(&sorted_copy);
	return (sorted_copy);
}
