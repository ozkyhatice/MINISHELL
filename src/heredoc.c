/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:33 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 20:51:52 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	exit(1);
}

static void	heredoc_read(char *end, int write_fd)
{
	char	*input;
	char	*heredoc;
	int 	flag;

	flag = 0;
	heredoc = NULL;
	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input || same_str(input, end))
		{
			if (heredoc && flag == 0)
			{
				write(write_fd, heredoc, ft_strlen(heredoc));
				flag = 1;
			}
			else
				write(write_fd, heredoc, 1);
			if (heredoc)
				free(heredoc);
			if (input)
				free(input);
			return ;
		}
		heredoc = ft_strdup("");
		heredoc = ft_strjoin(heredoc, input);
		heredoc = ft_strjoin(heredoc, "\n");
		if (input)
			free(input);
	}
	g_sig = AFTER_HEREDOC;
}

void	init_heredoc(t_shell *shell)
{
	t_parse_node	*p_head;
	t_exec_node		*e_head;
	int				fd[2];
	int				pid;
	int				stat;

	p_head = shell->parse_head;
	e_head = shell->exec_head;
	stat = 0;
	while (p_head)
	{
		while (p_head && p_head->type != PIPE)
		{
			if (p_head->type == 5)
			{
				g_sig = IN_HEREDOC;
				pipe(fd);
				pid = fork();
				if (pid == 0)
				{
					close(fd[0]);
					signal(SIGINT, interrupt_here_document);
					heredoc_read(p_head->next->word, fd[1]);
					close(fd[1]);
					exit(0);
				}
				else
				{
					close(fd[1]);
					waitpid(pid, &stat, 0);
					if (stat == 0)
					{
						if (e_head->heredoc)
							free(e_head->heredoc);
						e_head->heredoc = get_line(fd[0]);
						//close(fd[0]);
						if (!e_head->heredoc)
							exit(EXIT_FAILURE);
					}
					else
					{
						ft_free_nodes(shell);
						return ;
					}
				}
				g_sig = AFTER_HEREDOC;
			}
			p_head = p_head->next;
		}
		if (p_head)
			p_head = p_head->next;
		e_head = e_head->next;
	}
}
