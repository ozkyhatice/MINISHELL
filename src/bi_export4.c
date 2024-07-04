/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:12 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:13 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_argument(char *arg, t_shell *shell)
{
	if (ft_strchr(arg, '=') != NULL)
		add_export(shell, arg);
	else if (ft_check_syntax(arg))
		print_invalid_identifier_error(arg, shell);
	else
		add_environment(shell, arg, "");
}

void	print_exported_variable(t_env *env)
{
	sort_env_list(env);
	printf("declare -x %s", env->name);
	if (env->content && !is_full_space(env->content))
		printf("=\"%s\"", env->content);
	printf("\n");
}

void	print_invalid_identifier_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->ex_status = 1;
}

void	free_export_utils(t_env *tmp, t_env *tmp2)
{
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->content);
		free(tmp->name);
		free(tmp);
		tmp = tmp2;
	}
}
