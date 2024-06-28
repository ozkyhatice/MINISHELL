/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aredir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:04 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 16:52:48 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_set_error_close(t_shell *shell, t_args *head)
// {
// 	head->forward_cmd = 1;
// 	shell->exit_flag = 0;
// 	shell->exit_status = 1;
// 	if (head->in_redir > 0)
// 	{
// 		close(head->in_redir);
// 		head->in_redir = -1;
// 	}
// 	if (head->out_redir > 0)
// 	{
// 		close(head->out_redir);
// 		head->out_redir = -1;
// 	}
// }
void	ft_red_less(t_exec_node *ex, t_red *head_redir, t_shell *shell)
{
	int	fd;

	fd = open(head_redir->name, O_RDONLY);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
		else if (access(head_redir->name, R_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_PERM);
		shell->er_status = 1;
		shell->ex_status = 1;
	}
	if (ex->in != 0)
		close(ex->in);
	ex->in = fd;
	if (ex->here_path != NULL)
	{
		unlink("tmpfile");
		ex->here_path = NULL;
	}
}

void	ft_red_great(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int	fd;

	fd = open(head_redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
		else if (access(head_redir->name, W_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_PERM);
		shell->er_status = 1;
		shell->ex_status = 1;
		return ;
		// Hata durumunda erken çıkış
	}
	if (head->out != 1)
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
			ft_putstr_fd("sh.it: ", 2);
			ft_putstr_fd(head_redir->name, 2);
			ft_putendl_fd(E_NOFILE, 2);
		}
		else if (access(head_redir->name, W_OK) == -1)
		{
			ft_putstr_fd("sh.it: ", 2);
			ft_putstr_fd(head_redir->name, 2);
			ft_putendl_fd(E_PERM, 2);
		}
		shell->er_status = 1;
		shell->ex_status = 1;
	}
	if (head->out != 1)
		close(head->out);
	head->out = fd;
}

void	ft_heredoc(char *eof, int fd)
{
	char	*line;
	int		g_sig;

	g_sig = IN_HEREDOC;
	while (1 && g_sig != AFTER_HEREDOC)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if ((ft_strncmp(line, eof, ft_strlen(line)) == 0)
			&& ft_strlen(line) == ft_strlen(eof))
		{
			free(line);
			break ;
		}
		if (*line == 0x0)
		{
			free(line);
			continue ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
}

void	ft_redirection(t_shell *shell)
{
	t_exec_node	*ex;
	t_red		*ex_redir;

	ex = shell->exec_head;
	init_heredoc(shell);
	while (ex && shell->ex_status == 0)
	{
		ex_redir = ex->redirection_head;
		while (ex_redir && shell->er_status != 1) //
		{
			if (ex_redir->type == OUTPUT)
				ft_red_great(ex, ex_redir, shell);
			else if (ex_redir->type == APPENDOUT)
				ft_red_dgreat(ex, ex_redir, shell);
			else if (ex_redir->type == INPUT)
				ft_red_less(ex, ex_redir, shell);
			ex_redir = ex_redir->next;
		}
		if (shell->er_status == 1)
			exit(1);
		// shell->ex_status = 1;
		ex = ex->next;
	}
	// ft_check_heredoc_sig(shell);
}
