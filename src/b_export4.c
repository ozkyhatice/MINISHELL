/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:38:51 by relvan            #+#    #+#             */
/*   Updated: 2024/06/30 04:38:53 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_env_nodes(t_env *a, t_env *b)
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

void	sort_env_list(t_env **head)
{
	t_env	*current;
	t_env	*next_node;
	int		sorted;

	if (!head || !*head)
		return ;
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
