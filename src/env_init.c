/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:49 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:50 by akdemir          ###   ########.fr       */
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

t_env	*env_lstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	env_lstadd_back(t_env **lst, t_env *new)
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
}
