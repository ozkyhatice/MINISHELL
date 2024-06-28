/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:52 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 14:36:06 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	onequote_trim(t_shell *shell, char *word, int *i)
{
	int		s;
	char	*str;

	*i += 1;
	str = NULL;
	while (word[*i] && word[*i] != '\'')
	{
		s = *i;
		while (word[*i] && word[*i] != '\'')
			*i += 1;
		if (str)
			free(str);
		str = ft_substr(word, s, *i - s);
		if (str)
		{
			add_parse_subnode(shell, str);
			free(str);
		}
	}
	if (word[*i] == '\'')
		*i += 1;
}

static void	doublequote_trim(t_shell *shell, char *word, int *i)
{
	int		s;
	char	*str;

	*i += 1;
	str = NULL;
	while (word[*i] && word[*i] != '\"')
	{
		s = *i;
		while (word[*i] && word[*i] != '\"')
			*i += 1;
		if (str)
			free(str);
		str = ft_substr(word, s, *i - s);
		if (str)
		{
			add_parse_subnode(shell, str);
			free(str);
		}
	}
	if (word[*i] == '\"')
		*i += 1;
}

static char	*trim_quote(t_shell *shell, char *word)
{
	int		i;
	int		s;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (word[i])
	{
		if (word[i] == '\'')
			onequote_trim(shell, word, &i);
		else if (word[i] == '\"')
			doublequote_trim(shell, word, &i);
		else
		{
			s = i;
			while (word[i] && word[i] != '\"' && word[i] != '\'')
				i++;
			if (tmp_str)
				free(tmp_str);
			tmp_str = ft_substr(word, s, i - s);
			if (tmp_str)
				add_parse_subnode(shell, tmp_str);
		}
	}
	tmp_str = ft_strjoin_subnode(shell->subnode_head);
	ft_free_subnodes(shell);
	return (tmp_str);
}

void	quote_remove(t_shell *shell)
{
	t_parse_node	*node;
	char			*str;

	node = shell->parse_head;
	while (node)
	{
		if (ft_exist(node->word, '\"') || ft_exist(node->word, '\''))
		{
			str = ft_strdup(node->word);
			if (node->word)
				free(node->word);
			node->word = trim_quote(shell, str);
			free(str);
		}
		node = node->next;
	}
}
