/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:58 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:59 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	quote_dollar(t_shell *shell, char *word, int *i)
{
	int		s;
	char	*str;

	*i += 1;
	str = NULL;
	add_parse_subnode(shell, "\"");
	while (word[*i] && word[*i] != '\"')
	{
		if (word[*i] == '$')
			do_dollar(shell, word, i);
		else
		{
			s = *i;
			while (word[*i] && word[*i] != '$' && word[*i] != '\"')
				*i += 1;
			str = ft_substr(word, s, *i - s);
			if (str)
				add_parse_subnode(shell, str);
			if (str)
				free(str);
		}
	}
	if (word[*i] == '\"')
		*i += 1;
	add_parse_subnode(shell, "\"");
}

static void	onequote_split(t_shell *shell, char *word, int *i)
{
	int		s;
	char	*str;

	*i += 1;
	str = NULL;
	add_parse_subnode(shell, "\'");
	while (word[*i] && word[*i] != '\'')
	{
		s = *i;
		while (word[*i] && word[*i] != '\'')
			*i += 1;
		str = ft_substr(word, s, *i - s);
		if (str)
		{
			add_parse_subnode(shell, str);
			free(str);
		}
	}
	if (word[*i] == '\'')
		*i += 1;
	add_parse_subnode(shell, "\'");
}

int	trim_quote_dllr(t_shell *shell, char *w, int i, char *tmp_str)
{
	int		s;

	s = i;
	while (w[i] && w[i] != '$' && w[i] != '\"' && w[i] != '\'')
		i++;
	if (tmp_str)
		free(tmp_str);
	tmp_str = ft_substr(w, s, i - s);
	if (tmp_str)
		add_parse_subnode(shell, tmp_str);
	return (i);
}

static char	*parse_dollar(t_shell *shell, char *word)
{
	int		i;
	char	*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (word[i])
	{
		if (word[i] == '\'')
			onequote_split(shell, word, &i);
		else if (word[i] == '\"')
			quote_dollar(shell, word, &i);
		else if (word[i] == '$')
			do_dollar(shell, word, &i);
		else
			i = trim_quote_dllr(shell, word, i, tmp_str);
	}
	tmp_str = ft_strjoin_subnode(shell->subnode_head);
	ft_free_subnodes(shell);
	return (tmp_str);
}

void	split_dollar(t_shell *shell)
{
	t_parse_node	*node;
	char			*tmp;

	node = shell->parse_head;
	while (node)
	{
		if (ft_exist(node->word, '$'))
		{
			tmp = ft_strdup(node->word);
			if (node->word)
				free(node->word);
			node->word = parse_dollar(shell, tmp);
			free(tmp);
		}
		node = node->next;
	}
}
