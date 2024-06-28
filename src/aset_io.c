/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aset_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:09 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 13:05:17 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_rev(t_exec_node *ex)
{
	dup2(ex->std_in, 0);
	dup2(ex->std_out, 1);
	close(ex->std_in);
	close(ex->std_out);
}

void	set_io(t_exec_node *ex)
{
	ex->std_in = dup(0);
	ex->std_out = dup(1);
	if (ex->out > 2)
	{
		dup2(ex->out, STDOUT_FILENO);
		close(ex->out);
	}
	if (ex->in > 2)
	{
		dup2(ex->in, STDIN_FILENO);
		close(ex->in);
	}
}
