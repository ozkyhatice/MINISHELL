/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:47:28 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:47:29 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	in_control(t_exec_node *ex)
{
	if (ex->in != -3)
		close(ex->in);
}

void	ft_red_less(t_exec_node *ex, t_red *h_red, t_shell *shell)
{
	int	fd;

	fd = open(h_red->name, O_RDONLY);
	if (fd < 0)
	{
		if (access(h_red->name, F_OK) == -1)
		{
			ft_error_msg(NULL, h_red->name, E_NOFILE);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
		else if (access(h_red->name, R_OK) == -1)
		{
			ft_error_msg(NULL, h_red->name, E_PERM);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
	}
	in_control(ex);
	ex->in = fd;
	if (ex->here_path != NULL)
	{
		unlink("tmpfile");
		ex->here_path = NULL;
	}
}

void	redir_name_expand(t_red *h_red, char *str, t_env *env)
{
	char	**tmp;
	char	*tmp2;

	tmp2 = h_red->name;
	if (str[0] == '.' && str[1] == '/')
	{
		tmp = ft_split(ft_getenv(env, "PWD"), ':');
		if (tmp[0] == NULL)
		{
			ft_free_arr(tmp);
			return ;
		}
		if (tmp2)
			free(tmp2);
		h_red->name = ft_strjoin(tmp[0], str + 1);
		ft_free_arr(tmp);
	}
}

void	ft_red_great(t_exec_node *head, t_red *h_red, t_shell *shell)
{
	int	fd;

	redir_name_expand(h_red, h_red->name, shell->env_l);
	fd = open(h_red->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(h_red->name, F_OK) == -1)
		{
			ft_error_msg(NULL, h_red->name, E_NOFILE);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
		else if (access(h_red->name, R_OK) == -1)
		{
			ft_error_msg(NULL, h_red->name, E_PERM);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
	}
	if (head->out != -3)
		close(head->out);
	head->out = fd;
}

void	ft_red_dgreat(t_exec_node *head, t_red *h_red, t_shell *shell)
{
	int	fd;

	fd = open(h_red->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		if (access(h_red->name, F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(h_red->name, 2);
			ft_putendl_fd(E_NOFILE, 2);
		}
		else if (access(h_red->name, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(h_red->name, 2);
			ft_putendl_fd(E_PERM, 2);
		}
		shell->er_status = 0;
		shell->ex_status = 1;
	}
	if (head->out != -3)
		close(head->out);
	head->out = fd;
}
