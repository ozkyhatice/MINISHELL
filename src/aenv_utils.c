/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aenv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:29 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/28 12:15:31 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
	//burda ne yapmış anlamadık ihtiyaç olmadığı kanaatindeyiz

// char	**get_env_cpy(t_shell *shell) //incele sil
// {
// 	char	**envlist;
// 	char	*temp_env;
// 	t_env	*temp_envlist;

// 	envlist = NULL;
// 	temp_envlist = shell->env_l;
// 	while (temp_envlist)
// 	{
// 		if (temp_envlist->content)
// 		{
// 			temp_env = NULL;
// 			temp_env = ft_strjoin(temp_env, temp_envlist->name);
// 			temp_env = ft_strjoin(temp_env, "=");
// 			temp_env = ft_strjoin(temp_env, temp_envlist->content);
// 			envlist = dynamic_malloc(envlist, temp_env);
// 		}
// 		temp_envlist = temp_envlist->next;
// 	}
// 	return (envlist);
// }

// int	search_path(t_env *env_l, char *str)
// {
// 	t_env	*temp_env;

// 	temp_env = env_l;
// 	while (temp_env)
// 	{
// 		if (!ownstrcmp(temp_env->name, str))
// 		{
// 			if (!ownstrcmp(temp_env->name, "PWD"))
// 				if (temp_env->content[0] != '/')
// 					return (0);
// 			return (1);
// 		}
// 		temp_env = temp_env->next;
// 	}
// 	return (0);
// }

// char	**path_create(t_shell *shell, t_exec_node *ex, char **path)
// {
// 	int	i;

// 	if (ex->cmd && ex->cmd[0] == '/')
// 	{
// 		i = -1;
// 		while (shell->path && shell->path[++i])
// 			path = dynamic_malloc(path, ex->cmd);
// 		return (path);
// 	}
// 	i = -1;
// 	while (shell->path && shell->path[++i])
// 		path = dynamic_malloc(path, ft_strjoin(shell->path[i],
// 					ex->cmd));
// 	return (path);
// }

// char	*get_cmd(t_shell *shell, t_exec_node *ex)
// {
// 	char	**path;
// 	int		i;
// 	char	*cmd;
// 	char	cwd[256];

// 	path = NULL;
// 	path = path_create(shell, ex, path);
// 	i = -1;
// 	cmd = ex->cmd;
// 	while (path && path[++i])
// 		if (!access(path[i], F_OK) && !access(path[i], X_OK))
// 			break ;
// 	if (path && path[i])
// 		cmd = ft_strdup(path[i]);
// 	if (!search_path(shell->env_l, "PATH"))
// 		cmd = ex->cmd;
// 	if (ex->cmd && ex->cmd[0] == '.' && ex->cmd[1] == '/')
// 	{
// 		cmd = ft_strdup(getcwd(cwd, 256));
// 		cmd = ft_strjoin(cmd, ft_substr(ex->cmd, 1,
// 					ft_strlen(ex->cmd) - 1));
// 	}
// 	double_str_free(path);
// 	return (cmd);
// }
