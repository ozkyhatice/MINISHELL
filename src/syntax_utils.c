/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:20 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:46:21 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bracket_ctrl(t_shell *shell, t_parse_node *tmp)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (tmp->word[++i])
	{
		if (ft_isquote(tmp->word[i]))
		{
			quote = tmp->word[i];
			i++;
			while (tmp->word[i] && tmp->word[i] != quote)
				i++;
		}
		if (tmp->word[i] == '(')
		{
			shell->br_type = L_BRACKET;
			shell->l_br++;
		}
		if (tmp->word[i] == ')')
		{
			shell->r_br++;
			shell->br_type = R_BRACKET;
		}
	}
}

int	ft_print_control(int count, char c)
{
	if (count == 3 && c == '|')
		return (err_msg("|"));
	if (count > 3 && c == '|')
		return (err_msg("||"));
	if (count == 4 && c == '<')
		return (err_msg("<"));
	if (count == 5 && c == '<')
		return (err_msg("<<"));
	if (count > 5 && c == '<')
		return (err_msg("<<<"));
	if (count == 4 && c == '>')
		return (err_msg(">"));
	if (count == 5 && c == '>')
		return (err_msg(">>"));
	if (count > 5 && c == '>')
		return (err_msg(">>>"));
	else
		return (0);
}

int	control_howmany(char *str, char c)
{
	int		i;
	char	quote;
	int		count;
	int		re_code;

	i = 0;
	count = 0;
	re_code = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (str[i] == c)
			count++;
		i++;
	}
	re_code = ft_print_control(count, c);
	return (re_code);
}

int	err_msg(char *str)
{
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\'", 2);
	return (1);
}

int	istoken2(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (1);
	else if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (1);
	else if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (1);
	else
		return (0);
}
