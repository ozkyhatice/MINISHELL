/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:14 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:15 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_content;

	temp_name = a->name;
	temp_content = a->content;
	a->name = b->name;
	a->content = b->content;
	b->name = temp_name;
	b->content = temp_content;
}

void	sort_env_list(t_env *env_l)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (env_l == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = env_l;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_env	*copy_env_node(t_env *node)
{
	t_env	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(node->name);
	new_node->content = ft_strdup(node->content);
	new_node->next = NULL;
	return (new_node);
}

void	cp_env_list(t_env *tmp, t_env **new_list, t_env **last_node)
{
	t_env	*new_node;

	new_node = copy_env_node(tmp);
	if (!new_node)
	{
		while (*new_list)
		{
			free((*new_list)->name);
			free((*new_list)->content);
			free(*new_list);
			*new_list = (*new_list)->next;
		}
	}
	if (!*new_list)
		*new_list = new_node;
	else
		(*last_node)->next = new_node;
	*last_node = new_node;
}

t_env	*copy_env_list(t_env *env_l)
{
	t_env	*new_list;
	t_env	*tmp;
	t_env	*last_node;

	new_list = NULL;
	tmp = env_l;
	last_node = NULL;
	while (tmp)
	{
		cp_env_list(tmp, &new_list, &last_node);
		tmp = tmp->next;
	}
	return (new_list);
}
