/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:59 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/29 09:08:15 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		}
		node = node->next;
	}
}
