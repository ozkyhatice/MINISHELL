/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:39:02 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 16:39:19 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_first_builtin(t_shell *shell, t_exec_node *ex)
{
	set_io(ex);
	builtin_run(ex, shell);
	ft_dup_rev(ex);
}
