/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 07:38:07 by relvan            #+#    #+#             */
/*   Updated: 2024/07/01 07:39:15 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	spec_dol(t_shell *shell, char *str)
{
	add_parse_subnode(shell, "minishell");
	add_parse_subnode(shell, str + 1);
}
