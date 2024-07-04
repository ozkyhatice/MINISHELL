/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:15 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:16 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_parse_node	*create_parse_node(const char *s)
{
	t_parse_node	*new;

	new = malloc(sizeof(t_parse_node));
	if (new)
	{
		new->type = get_token(s);
		new->word = ft_strdup(s);
		new->heredoc = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void	add_parse_node(t_shell *shell, char *s)
{
	t_parse_node	*new;

	if (s[0] != '\0' && s)
	{
		new = create_parse_node(s);
		if (shell->parse_head == NULL && new)
		{
			new->prev = NULL;
			shell->parse_head = new;
			shell->parse_tail = new;
		}
		else
		{
			new->prev = shell->parse_tail;
			shell->parse_tail->next = new;
			shell->parse_tail = new;
		}
	}
}

void	print_parse_node(t_shell *shell)
{
	t_parse_node	*current;

	current = shell->parse_head;
	printf("\n");
	while (current != NULL)
	{
		printf("parse_node#%s: type:#%u\n", current->word, current->type);
		current = current->next;
	}
	printf("\n");
}

void	ft_free_nodes(t_shell *shell)
{
	t_parse_node	*current;
	t_parse_node	*next;

	current = shell->parse_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		free(current->heredoc);
		free(current);
		current = next;
	}
	shell->parse_head = NULL;
	shell->parse_tail = NULL;
}
