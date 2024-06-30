/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relvan <relvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:51:48 by akdemir           #+#    #+#             */
/*   Updated: 2024/06/30 21:01:19 by relvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_intarr(int **num, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->c_pipe - 1)
	{
		free(num[i]);
		i++;
	}
	free(num);
}

char	*is_dir3(char *cmd, t_env *env)
{
	char	**str;

	if (cmd[0] == '~')
	{
		str = ft_split(ft_getenv(env, "HOME"), ':');
		if (str[0] == NULL)
		{
			ft_free_arr(str);
			return (NULL);
		}
		cmd = ft_strjoin(str[0], cmd + 1);
		ft_free_arr(str);
	}
	return (cmd);
}

void	ft_free_cmdpath(char *cmdpath, char *tmp)
{
	free(tmp);
	free(cmdpath);
}

char	*getcmdpath(char *cmd, char **path, t_env *env)
{
	int		i;
	char	*cmdpath;
	char	*tmp;

	i = -1;
	cmd = is_dir3(cmd, env);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		is_dir(cmd);
		return (cmd);
	}
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		if (access(cmdpath, F_OK) == 0)
		{
			free(tmp);
			return (cmdpath);
		}
		ft_free_cmdpath(cmdpath, tmp);
	}
	return (NULL);
}

void	define_rtype(t_parse_node *node, t_exec_node *exnode)
{
	t_parse_node	*tmp;
	t_exec_node		*ex;

	tmp = node;
	ex = exnode;
	(void)ex;
	while (tmp)
	{
		if (tmp->type == R_REDIR)
			tmp->next->type = OUTPUT;
		else if (tmp->type == APPEND)
			tmp->next->type = APPENDOUT;
		else if (tmp->type == L_REDIR)
			tmp->next->type = INPUT;
		else if (tmp->type == HEREDOC)
			tmp->next->type = HD;
		tmp = tmp->next;
	}
}
