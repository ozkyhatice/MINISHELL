/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:19 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:49:20 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_export(t_shell *shell, char *arg)
{
	char	**splitted;

	splitted = ft_split(arg, '=');
	if (ft_check_syntax(splitted[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		shell->ex_status = 1;
		ft_free_arr(splitted);
		return ;
	}
	if (!splitted[1])
		add_environment(shell, splitted[0], "");
	else
		add_environment(shell, splitted[0], splitted[1]);
	ft_free_arr(splitted);
}

int	ft_check_syntax(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isname(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	run_export(t_exec_node *cmd, t_shell *shell)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	if (!cmd->cmd[1])
	{
		tmp = copy_env_list(shell->env_l);
		tmp2 = tmp;
		while (tmp2)
		{
			print_exported_variable(tmp2);
			tmp2 = tmp2->next;
		}
		free_export_utils(tmp, tmp2);
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
