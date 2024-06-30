/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:12:13 by relvan            #+#    #+#             */
/*   Updated: 2024/06/30 23:12:15 by relvan           ###   ########.fr       */
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
