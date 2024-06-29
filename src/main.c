/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:46 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/29 19:47:38 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		exit_code;

	if (argc > 1)
	{
		printf("minishell: %s: No such file or directory", argv[1]);
		return (127);
	}
	shell = ft_calloc(1, sizeof(t_shell));
	g_sig = 0;
	if (!shell)
		exit(0);
	ft_init_signals();
	initalizer(shell, env);
	exit_code = shell->ex_status;
	return (exit_code);
}
