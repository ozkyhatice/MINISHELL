/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:19 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:21 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parameters_count(char **str)
{
	int	count;

	count = 0;
	while (str && *(str++))
		count++;
	return (count);
}

int	env_name_control(char *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!env || env[i] == ' ' || env[i] == '=')
		return (0);
	if (ft_isalpha(env[i]) || env[i] == '_')
		flag = 1;
	while (env[i] && env[i] != ' ' && env[i] != '=' && flag == 1)
	{
		if ((!ft_isdigit(env[i]) && !ft_isalpha(env[i]) && env[i] != '_')
			|| !flag)
			return (0);
		i++;
	}
	if (env[i] != '=' && env[i])
		return (0);
	return (1);
}

int	env_arg_control(char *env)
{
	if (env_name_control(env))
		return (1);
	printf("-not a valid identifier--\n");
	return (0);
}

void	delete_env(t_shell *shell, char *name)
{
	t_env	*env;
	t_env	*temp_env;

	env = shell->env_l;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			if (env->content)
				free(env->content);
			free(env->name);
			if (shell->env_l == env)
				shell->env_l = shell->env_l->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}

void	run_unset(t_shell *shell)
{
	char	**temp_name;
	int		array_len;

	array_len = parameters_count(shell->exec_head->cmd);
	if (array_len > 1)
	{
		temp_name = shell->exec_head->cmd;
		while (*(++temp_name))
		{
			if (!env_arg_control(*temp_name))
			{
				printf("not a valid identifier\n");
				continue ;
			}
			else
				delete_env(shell, *temp_name);
		}
	}
}
