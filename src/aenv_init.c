/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aenv_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:48:42 by senyilma          #+#    #+#             */
/*   Updated: 2024/06/27 12:20:21 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_listnew(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env	*lst)
{
	t_env	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	env_lstadd_back(t_env	**lst, t_env	*new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		env_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

// void	path_init(t_shell *shell)
// {
// 	t_env	*env_l;
// 	int		i;
// 	char	**temp_command;
// 	char	*join;

// 	env_l = shell->env_l;
// 	shell->path = NULL;
// 	if (!search_path(env_l, "PATH"))
// 		return ;
// 	while (env_l)
// 	{
// 		if (!ownstrcmp(env_l->name, "PATH"))
// 			break ;
// 		env_l = env_l->next;
// 	}
// 	temp_command = ft_split(env_l->content, ':');
// 	i = -1;
// 	while (temp_command[++i])
// 	{
// 		join = ft_strjoin(temp_command[i], "/");
// 		shell->path = dynamic_malloc(shell->path, join);
// 		free(join);
// 	}
// 	free(temp_command);
// }

void	env_init(t_shell *shell, char **env)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = -1;
	while (env && env[++i])
	{
		end = 0;
		while (env[i][end])
		{
			start = end;
			while (env[i][end] && env[i][end] != '=')
				end++;
			name = ft_substr(env[i], start, end);
			end++;
			start = end;
			while (env[i][end])
				end++;
			content = ft_substr(env[i], start, end);
			env_lstadd_back(&shell->env_l, env_listnew(name, content));
		}
	}
	//path_init(shell);// bak
}
