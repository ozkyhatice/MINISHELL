/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:04 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/29 14:48:35 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_red_less(t_exec_node *ex, t_red *head_redir, t_shell *shell)
{
	int	fd;

	fd = open(head_redir->name, O_RDONLY);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
		{
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
		else if (access(head_redir->name, R_OK) == -1)
		{
			ft_error_msg(NULL, head_redir->name, E_PERM);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
	}
	if (ex->in != -3)
		close(ex->in);
	ex->in = fd;
	if (ex->here_path != NULL)
	{
		unlink("tmpfile");
		ex->here_path = NULL;
	}
}

void	redir_name_expand(t_red *head_redir, char  *str, t_env *env)
{
	char	**tmp;
	char	*tmp2;

	tmp2 = head_redir->name;
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
		head_redir->name = ft_strjoin(tmp[0], str + 1);
		ft_free_arr(tmp);
	}
}

void	ft_red_great(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int	fd;

	redir_name_expand(head_redir, head_redir->name, shell->env_l);
	fd = open(head_redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
		{
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
		else if (access(head_redir->name, R_OK) == -1)
		{
			ft_error_msg(NULL, head_redir->name, E_PERM);
			shell->ex_status = 1;
			shell->er_status = 0;
		}
	}
	if (head->out != -3)
		close(head->out);
	head->out = fd;
}

void	ft_red_dgreat(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int	fd;

	fd = open(head_redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(head_redir->name, 2);
			ft_putendl_fd(E_NOFILE, 2);
		}
		else if (access(head_redir->name, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(head_redir->name, 2);
			ft_putendl_fd(E_PERM, 2);
		}
		shell->er_status = 0;
		shell->ex_status = 1;
	}
	if (head->out != -3)
		close(head->out);
	head->out = fd;
}

void    ft_redir_dless(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
    int    fd;

    if (head->in != 0)
        close(head->in);
    fd = open("tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
    if (fd < 0)
    {
        if (access(head_redir->name, F_OK) == -1)
            ft_error_msg(NULL, head_redir->name, E_NOFILE);
        else if (access(head_redir->name, R_OK) == -1)
            ft_error_msg(NULL, head_redir->name, E_PERM);
        shell->ex_status = 1;
        return;
    }
    ft_heredoc(head_redir->name, fd);
    fd = open("tmpfile", O_RDONLY);
    head->in = fd;
    if (head->here_path != NULL)
    {
        unlink("tmpfile");
        head->here_path = NULL;
    }
    head->here_path = ft_strdup("tmpfile");
}

void    ft_heredoc(char *eof, int fd)
{
    char    *line;

    while (1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if ((ft_strncmp(line, eof, ft_strlen(eof)) == 0) && ft_strlen(line) == ft_strlen(eof))
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
    close(fd);
    g_sig = AFTER_HEREDOC;
}



