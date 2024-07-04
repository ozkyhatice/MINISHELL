/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:00 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:01 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	spec_dol(t_shell *shell, char *str)
{
	add_parse_subnode(shell, "minishell");
	add_parse_subnode(shell, str + 1);
}
