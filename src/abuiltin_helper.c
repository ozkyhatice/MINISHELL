/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abuiltin_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 02:17:34 by mkaragoz          #+#    #+#             */
/*   Updated: 2024/06/24 17:04:44 by abkiraz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//extern t_data	g_data;

int	run_pwd(void)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
	//g_prime->exit_code = 0;
}

// void	add_export(char	*arg)
// {
// 	char	**splitted;

// 	splitted = ft_split(arg, '=');
// 	if (!splitted[1])
// 		add_environment(splitted[0], "");
// 	else
// 		add_environment(splitted[0], splitted[1]);
// 	smart_free_strs(splitted);
// }

// void	*unset_node(t_env *node)
// {
// 	void	*tmp;

// 	smart_free(node->key);
// 	smart_free(node->value);
// 	tmp = node->next;
// 	free(node);
// 	return (tmp);
// }

int	run_echo(t_exec_node *ex)
{
	bool	n;
	int		i;

	i = 1;
	n = false;
	while (ex->cmd[i])
	{
		if (i == 1 && !ft_strncmp("-n", ex->cmd[i], 2) && \
			check_echo_n(ex->cmd[i]))
		{
			n = true;
			i++;
			continue ;
		}
		printf("%s", ex->cmd[i]);
		if (ex->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	return (1);
}
