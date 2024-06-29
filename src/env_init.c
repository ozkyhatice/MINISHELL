/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:25 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 18:51:24 by relvan           ###   ########.fr       */
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
void swap_env_nodes(t_env *a, t_env *b)
{
    char *temp_name = a->name;
    char *temp_content = a->content;
    a->name = b->name;
    a->content = b->content;
    b->name = temp_name;
    b->content = temp_content;
}

void sort_env_list(t_env **head)
{
    if (!head || !*head)
        return;

    int sorted;
    t_env *current;
    t_env *next_node;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        current = *head;

        while (current->next)
        {
            next_node = current->next;
            if (ft_strcmp(current->name, next_node->name) > 0)
            {
                swap_env_nodes(current, next_node);
                sorted = 0;
            }
            current = current->next;
        }
    }
}

void	env_p_init(t_shell *shell, char **env)
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
			env_lstadd_back(&shell->env_p, env_listnew(name, content));
		}
	}
}
