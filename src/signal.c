/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:17 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:18 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	if (g_sig == IN_HEREDOC)
	{
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else if (g_sig == IN_CMD)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_sig = AFTER_CMD;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig = 1;
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
}
