/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:10 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:46:11 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

enum e_token	get_token(const char *str)
{
	int				len;
	enum e_token	token;

	len = ft_strlen(str);
	token = 0;
	if (len == 2 || len == 1 || len == 3)
		token = char_token(str);
	else
		token = WORD;
	return (token);
}

enum e_token	char_token(const char *str)
{
	if (same_str(str, "||"))
		return (OR);
	else if (same_str(str, "&&"))
		return (AND);
	else if (same_str(str, "<<"))
		return (HEREDOC);
	else if (same_str(str, ">>"))
		return (APPEND);
	else if (same_str(str, "|"))
		return (PIPE);
	else if (same_str(str, ">"))
		return (R_REDIR);
	else if (same_str(str, "<"))
		return (L_REDIR);
	else if (same_str(str, ")"))
		return (R_BRACKET);
	else if (same_str(str, "("))
		return (L_BRACKET);
	else if (same_str(str, ">>>"))
		return (NEWLINE_N_R);
	else if (same_str(str, "<<<"))
		return (NEWLINE_N);
	else
		return (WORD);
}
