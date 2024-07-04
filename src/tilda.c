/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:14 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:46:15 by akdemir          ###   ########.fr       */
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
			free(str);
		}
		node = node->next;
	}
}
