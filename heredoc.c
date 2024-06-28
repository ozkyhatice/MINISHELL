/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:33 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 19:11:59 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	exit(1);
}

static void	handle_heredoc_end(char *input, char *heredoc, int write_fd)
{
	if (heredoc)
	{
		write(write_fd, heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
	if (input)
		free(input);
}

static void	read_input(char **input, char **heredoc)
{
	*input = readline("> ");
	if (*input)
	{
		*heredoc = ft_strjoin(*heredoc, *input);
		*heredoc = ft_strjoin(*heredoc, "\n");
		free(*input);
	}
}

static void	heredoc_read(char *end, int write_fd)
{
	char	*input;
	char	*heredoc;
	int		flag;

	input = NULL;
	heredoc = ft_strdup("");
	flag = 0;
	while (1)
	{
		read_input(&input, &heredoc);
		if (!input || same_str(input, end))
		{
			handle_heredoc_end(input, heredoc, write_fd);
			return ;
		}
	}
	g_sig = AFTER_HEREDOC;
}

static void	heredoc_child_process(int *fd, char *end)
{
	close(fd[0]);
	signal(SIGINT, interrupt_here_document);
	heredoc_read(end, fd[1]);
	exit(0);
}

void	stat_control(t_exec_node *e, int *fd, t_shell *s, int stat)
{
	if (stat == 0)
	{
		if (e->heredoc)
			free(e->heredoc);
		e->heredoc = get_line(fd[0]);
		close(fd[0]);
		if (!e->heredoc)
			exit(EXIT_FAILURE);
	}
	else
	{
		ft_free_nodes(s);
		return ;
	}
}

static void	proc(t_shell *s, t_parse_node *p, t_exec_node *e, int *fd)
{
	int	pid;
	int	stat;

	g_sig = IN_HEREDOC;
	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_child_process(fd, p->next->word);
	else
	{
		close(fd[1]);
		waitpid(pid, &stat, 0);
		stat_control(e, fd, s, stat);
	}
	close(fd[1]);
	g_sig = AFTER_HEREDOC;
}

void	init_heredoc(t_shell *shell)
{
	t_parse_node	*p_head;
	t_exec_node		*e_head;
	int				fd[2];
	int				stat;

	p_head = shell->parse_head;
	e_head = shell->exec_head;
	while (p_head)
	{
		while (p_head && p_head->type != PIPE)
		{
			if (p_head->type == 5)
				proc(shell, p_head, e_head, fd);
			p_head = p_head->next;
		}
		if (p_head)
			p_head = p_head->next;
		e_head = e_head->next;
	}
}
