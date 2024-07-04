/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:30 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:31 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir_dless(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int		fd;
	char	*str;

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
		return ;
	}
	ft_heredoc(head_redir->name, fd);
	fd = open("tmpfile", O_RDONLY);
	head->in = fd;
	if (head->here_path != NULL)
	{
		unlink("tmpfile");
		head->here_path = NULL;
	}
	str = "tmpfile";
	head->here_path = ft_strdup(str);
}

void	ft_heredoc(char *eof, int fd)
{
	char	*line;

	g_sig = IN_HEREDOC;
	while (1 && g_sig == IN_HEREDOC)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if ((ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			&& ft_strlen(line) == ft_strlen(eof))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	g_sig = AFTER_HEREDOC;
}
