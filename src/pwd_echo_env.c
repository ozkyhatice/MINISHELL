/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_echo_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:34 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:35 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_pwd(void)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

void	run_echo(t_exec_node *ex, t_shell *shell)
{
	bool	n;
	int		i;

	i = 1;
	n = false;
	while (ex->cmd[i] && !ft_strncmp("-n", ex->cmd[i], 2)
		&& check_echo_n(ex->cmd[i]))
	{
		n = true;
		i++;
	}
	while (ex->cmd[i])
	{
		printf("%s", ex->cmd[i]);
		if (ex->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	shell->ex_status = 0;
}

void	run_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env_l;
	while (env && env->content)
	{
		if (env->content[0] != '\0')
			printf("%s=%s\n", env->name, env->content);
		else if (!env->content)
			printf("%s=\n", env->name);
		env = env->next;
	}
}
