/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:12 by abkiraz           #+#    #+#             */
/*   Updated: 2024/07/01 04:45:47 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mark_expand(t_shell *shell)
{
	char	*tmp;

	tmp = NULL;
	if (g_sig == 1 || g_sig == AFTER_HEREDOC)
	{
		add_parse_subnode(shell, "1");
		g_sig = 0;
	}
	else if (g_sig == IN_CMD)
	{
		add_parse_subnode(shell, "130");
		g_sig = 0;
	}
	else
	{
		tmp = ft_itoa(shell->ex_status);
		add_parse_subnode(shell, tmp);
		free(tmp);
	}
}

void	special_dodollar(t_shell *shell, char *str)
{
	if (str[0] == '0')
	{
		add_parse_subnode(shell, "minishell");
		add_parse_subnode(shell, str + 1);
	}
	if (str[0] == '?')
	{
		mark_expand(shell);
		add_parse_subnode(shell, str + 1);
	}
}

void	do_dollar2(t_shell *shell, char *tmp)
{
	char	*env_value;
	char	*str;

	env_value = ft_getenv(shell->env_l, tmp);
	str = ft_strdup(tmp);
	if (str)
	{
		if (env_value)
			env_dollar(shell, env_value);
		else if ((str[0] >= '1' && str[0] <= '9') || str[0] == '*'
			|| str[0] == '@' || str[0] == '!')
			dollar_nullcontrol(shell, str);
		else if (special_dollar(str[0]))
			special_dodollar(shell, str);
		else
		{
			if (dollar_control(str[0]))
				add_dollar(shell, str);
			if (dollar_control2(str[0], shell, str))
				add_parse_subnode(shell, "");
		}
		free(str);
	}
}

void	do_dollar(t_shell *shell, char *str, int *i)
{
	char	*word;
	char	*tmp;
	int		s;

	word = ft_strdup(str);
	tmp = NULL;
	*i = *i + 1;
	s = *i;
	while (word[*i] && word[*i] != ' ' && word[*i] != '$' && word[*i] != '\"'
		&& word[*i] != '\'')
		*i = *i + 1;
	if (tmp)
		free(tmp);
	tmp = ft_substr(word, s, *i - s);
	if (tmp)
	{
		do_dollar2(shell, tmp);
		free(tmp);
	}
	if (word)
		free(word);
}
