/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subnode_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:15 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:16 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_subnode	*create_parse_node(const char *s)
{
	t_subnode	*new;

	new = malloc(sizeof(t_subnode));
	if (new)
	{
		new->word = ft_strdup(s);
		new->next = NULL;
	}
	return (new);
}

void	add_parse_subnode(t_shell *shell, char *s)
{
	t_subnode	*new;

	if (s[0] != '\0' && s)
	{
		new = create_parse_node(s);
		if (shell->subnode_head == NULL && new)
		{
			new->prev = NULL;
			shell->subnode_head = new;
			shell->subnode_tail = new;
		}
		else
		{
			new->prev = shell->subnode_tail;
			shell->subnode_tail->next = new;
			shell->subnode_tail = new;
		}
	}
}

void	print_subnode(t_shell *shell)
{
	t_subnode	*current;

	current = shell->subnode_head;
	printf("\n");
	while (current != NULL)
	{
		printf("\n%s->\n", current->word);
		current = current->next;
	}
	printf("\n");
}

void	ft_free_subnodes(t_shell *shell)
{
	t_subnode	*current;
	t_subnode	*next;

	current = shell->subnode_head;
	while (current != NULL)
	{
		next = current->next;
		if (current->word)
			free(current->word);
		free(current);
		current = next;
	}
	shell->subnode_head = NULL;
	shell->subnode_tail = NULL;
}

char	*ft_strjoin_subnode(t_subnode *node)
{
	t_subnode	*current;
	char		*str;
	char		*copy;
	char		*tmp;

	current = node;
	str = NULL;
	while (current)
	{
		if (!str)
			str = ft_strdup(current->word);
		else
		{
			copy = ft_strdup(current->word);
			if (copy)
			{
				tmp = str;
				str = ft_strjoin(str, copy);
				free(copy);
				free(tmp);
			}
		}
		current = current->next;
	}
	return (str);
}
