/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:15 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:16 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

int	check_and_update(t_shell *shell, char *name, char *content)
{
	t_env	*tmp;

	tmp = shell->env_l;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_environment(t_shell *shell, char *name, char *content)
{
	t_env	*new;
	t_env	*lst;

	if (!check_and_update(shell, name, content))
	{
		new = create_env(name, content);
		if (!new)
			return ;
		lst = env_lstlast(shell->env_l);
		if (lst == NULL)
		{
			shell->env_l = new;
		}
		else
		{
			lst->next = new;
		}
	}
}

int	ft_is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_isname(int c)
{
	return (ft_isalnum(c) || c == '_');
}
