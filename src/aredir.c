#include "../include/minishell.h"
void	ft_error_msg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("sh.it: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}
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
		// shell->exit_flag = 1;
		shell->ex_status = 1;
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

void	ft_red_great(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int	fd;

    fd = open(head_redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(2, "içerde misin evlat");
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
		else if (access(head_redir->name, W_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_PERM);
		// shell->exit_flag = 1;
		shell->ex_status = 1;
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
		// shell->exit_flag = 1;
		shell->ex_status = 1;
	}
	if (head->out != -3)
		close(head->out);
	head->out = fd;
}

void	ft_heredoc(char *eof, int fd)
{
	char	*line;

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
void	ft_redir_dless(t_exec_node *head, t_red *head_redir, t_shell *shell)
{
	int	fd;

	if (head->in != -3)
		close(head->in);
	fd = open("tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
	{
		if (access(head_redir->name, F_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_NOFILE);
		else if (access(head_redir->name, R_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_PERM);
		else if (access(head_redir->name, R_OK) == -1)
			ft_error_msg(NULL, head_redir->name, E_PERM);
		// shell->exit_flag = 1;
		shell->ex_status = 1;
	}
	ft_heredoc(head_redir->name, fd);
	fd = open("tmpfile", O_RDONLY);
	head->in = fd;
	if (head->here_path != NULL)
	{
		unlink("tmpfile");
		head->here_path = NULL;
	}
	head->here_path = ft_strdup(".tmpfile");
}
void	ft_redirection(t_shell	*shell)
{
	t_exec_node	*ex;
	t_red      	*ex_redir;

	ex = shell->exec_head;
	while (ex)
	{
		ex_redir = ex->redirection_head;
		while (ex_redir)// && shell->exit_flag != 1
		{
			if (ex_redir->type == OUTPUT)
				ft_red_great(ex, ex_redir, shell);
			else if (ex_redir->type == APPENDOUT)
				ft_red_dgreat(ex, ex_redir, shell);
			else if (ex_redir->type == INPUT)
				ft_red_less(ex, ex_redir, shell);
			else if (ex_redir->type == HD)
				ft_redir_dless(ex, ex_redir, shell);
			// else if (ft_which_redir(ex_redir->operator) == DGREAT)
			// 	ft_red_dgreat(ex, ex_redir, shell);
			// else if (ft_which_redir(ex_redir->operator) == DLESS)
			// 	ft_red_dless(ex, ex_redir, shell);
			ex_redir = ex_redir->next;
		}
		// if (shell->exit_flag == 1)
		// 	ft_set_error_close(shell, ex);
		ex = ex->next;
	}
	// ft_check_heredoc_sig(shell);
}