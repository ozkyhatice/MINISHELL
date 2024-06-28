/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abuiltin_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:14:58 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/28 18:25:33 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// extern t_data	g_data;

void	run_pwd(void)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

// void	add_export(char	*arg)
// {
// 	char	**splitted;

// 	splitted = ft_split(arg, '=');
// 	if (!splitted[1])
// 		add_environment(splitted[0], "");
// 	else
// 		add_environment(splitted[0], splitted[1]);
// 	smart_free_strs(splitted);
// }

// void	*unset_node(t_env *node)
// {
// 	void	*tmp;

// 	smart_free(node->name);
// 	smart_free(node->content);
// 	tmp = node->next;
// 	free(node);
// 	return (tmp);
// }

void	run_echo(t_exec_node *ex, int *extstat)
{
	bool	n;
	int		i;

	i = 1;
	n = false;
	while (ex->cmd[i])
	{
		if (i == 1 && !ft_strncmp("-n", ex->cmd[i], 2)
			&& check_echo_n(ex->cmd[i]))
		{
			n = true;
			i++;
			continue ;
		}
		printf("%s", ex->cmd[i]);
		if (ex->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	*extstat = 0;
	// return (1);
}

void	run_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env_l;
	while (env && env->content) //&& !is_full_space(env->content)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	// return (1);
}
