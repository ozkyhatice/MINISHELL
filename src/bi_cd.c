/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:22 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:23 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	go_dir(t_shell *shell, char *path, char **new)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(pwd);
		free(oldpwd);
		return (0);
	}
	*new = getcwd(NULL, 0);
	add_environment(shell, "PWD", *new);
	add_environment(shell, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return (1);
}

int	handle_cd_result(int res, char *dir, t_shell *shell, char **home)
{
	if (res == 0)
	{
		if (dir != NULL)
			ft_error_msg(dir, NULL, "No such file or directory");
		shell->ex_status = 1;
		if (home != NULL)
			free(*home);
		return (0);
	}
	shell->ex_status = 0;
	return (1);
}

int	cd_exec(t_shell *shell, t_exec_node **ex, char **tmp, char **new)
{
	int		res;
	char	*home;
	char	*tmp_env;

	res = -1;
	tmp_env = ft_getenv(shell->env_l, "HOME");
	home = ft_strdup(tmp_env);
	if ((*ex)->cmd[1] == NULL)
	{
		res = go_dir(shell, home, new);
		if (!handle_cd_result(res, NULL, shell, &home))
			return (0);
		*tmp = home;
		free(home);
	}
	else
	{
		res = go_dir(shell, (*ex)->cmd[1], new);
		if (!handle_cd_result(res, (*ex)->cmd[1], shell, &home))
			return (0);
		*tmp = (*ex)->cmd[1];
		free(home);
	}
	return (1);
}

int	run_cd(t_shell *shell, t_exec_node *ex)
{
	char	*curr;
	char	*tmp;
	char	*new;
	char	*home;
	int		res;

	res = -1;
	home = getcwd(NULL, 0);
	curr = ft_strdup(home);
	res = cd_exec(shell, &ex, &tmp, &new);
	if (!res)
	{
		free(curr);
		free(home);
		return (0);
	}
	add_environment(shell, "PWD", new);
	add_environment(shell, "OLDPWD", curr);
	free(new);
	free(curr);
	free(home);
	return (1);
}
