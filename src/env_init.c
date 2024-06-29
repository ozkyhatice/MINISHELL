/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:25 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 17:20:47 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_listnew(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		env_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	env_init(t_shell *shell, char **env)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = -1;
	while (env && env[++i])
	{
		end = 0;
		while (env[i][end])
		{
			start = end;
			while (env[i][end] && env[i][end] != '=')
				end++;
			name = ft_substr(env[i], start, end);
			end++;
			start = end;
			while (env[i][end])
				end++;
			content = ft_substr(env[i], start, end);
			env_lstadd_back(&shell->env_l, env_listnew(name, content));
		}
	}
}
t_env	*env_copy(t_env *env)
{
	t_env	*new_list = NULL;
	t_env	*current;

	while (env)
	{
		current = env_listnew(ft_strdup(env->name), ft_strdup(env->content));
		if (!current)
		{
			// Handle memory allocation failure
			// Free previously allocated nodes
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

void	env_sort(t_env **env)
{
	t_env	*current;
	t_env	*next;
	char	*tmp_name;
	char	*tmp_content;
	int		sorted;

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
				tmp_name = current->name;
				tmp_content = current->content;
				current->name = next->name;
				current->content = next->content;
				next->name = tmp_name;
				next->content = tmp_content;
				sorted = 0;
			}
			current = next;
		}
	}
}

t_env	*env_sorted_copy(t_env *env)
{
	t_env	*sorted_copy = env_copy(env);

	if (sorted_copy)
		env_sort(&sorted_copy);
	return (sorted_copy);
}