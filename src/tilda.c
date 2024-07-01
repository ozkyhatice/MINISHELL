/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:59 by abkiraz           #+#    #+#             */
/*   Updated: 2024/07/01 03:45:30 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parse_node	*get_next_node(t_parse_node *current, t_parse_node **prev)
{
	if (*prev)
		*prev = current;
	if (current)
		return (current->next);
	return (NULL);
}

void	tilda_control(t_shell *shell)
{
	t_parse_node	*node;
	char			**str;

	node = shell->parse_head;
	str = NULL;
	while (node)
	{
		if (same_str(node->word, "~"))
		{
			if (node->word)
				free(node->word);
			str = ft_split(ft_getenv(shell->env_l, "HOME"), ':');
			node->word = str[0];
			free(str);
		}
		node = node->next;
	}
}
