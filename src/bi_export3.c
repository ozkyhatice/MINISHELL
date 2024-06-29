/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:59:29 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/29 17:19:42 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_exported_variable(t_env *env)
{
	ft_sort_env(env);
	printf("declare -x %s", env->name);
	if (env->content && !is_full_space(env->content))
		printf("=\"%s\"", env->content);
	printf("\n");
}

static void	print_invalid_identifier_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->ex_status = 1;
}

static void	handle_argument(char *arg, t_shell *shell)
{
	if (ft_strchr(arg, '=') != NULL)
		add_export(shell, arg);
	else if (ft_check_syntax(arg))
		print_invalid_identifier_error(arg, shell);
	else
		add_environment(shell, arg, "");
}

int	run_export(t_exec_node *cmd, t_shell *shell)
{
	t_env	*tmp;
	int		i;

	if (!cmd->cmd[1])
	{
		tmp = shell->env_l;
		while (tmp)
		{
			print_exported_variable(tmp);
			tmp = tmp->next;
		}
		return (1);
	}
	i = 1;
	while (cmd->cmd[i])
	{
		handle_argument(cmd->cmd[i], shell);
		i++;
	}
	return (1);
}
