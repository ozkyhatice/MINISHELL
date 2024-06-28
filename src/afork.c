#include "../include/minishell.h"

void	ft_single_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	exnd = get_exec_node(shell->exec_head, i);
	path = getcmdpath(exnd->cmd[i], shell->path);
	exnd = get_exec_node(shell->exec_head, i);
	set_io(exnd);
	if (execve(path, exnd->cmd, NULL) == -1)
	{
		if (path == NULL)
		{
				ft_error_msg(exnd->cmd[0], NULL, "command not found");
				shell->ex_status = 127;
		}
		else if (ft_access(path))	
    	    ft_error_msg(path, NULL, "not authorize to execute");
	}
}

void	ft_multi_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	set_dup2(shell, i);
	exnd = get_exec_node(shell->exec_head, i);
	if (is_builtin(exnd->cmd[0]))
	{
		builtin_run(exnd, shell);

		// dprintf(2, "asdasdasdasdasdasa\n");
		//printf("----- builtin %d. kez------\n", i);
	}
	else 
	{
		path = getcmdpath(exnd->cmd[0], shell->path);
	// dprintf(2,"battı balık: %s\n", exnd->cmd[1]);
		if (execve(path, exnd->cmd, NULL) == -1)
		{
			if (path == NULL)
			{
				ft_error_msg(exnd->cmd[0], NULL, "command not found");
				shell->ex_status = 127;
			}
			else if (ft_access(path))	
				ft_error_msg(path, NULL, "not authorize to execute");

		}
	}
}

int	ft_execve(t_shell *shell, t_exec_node *ex, int i)
{	
	if (shell->c_pipe == 1 && is_builtin(ex->cmd[0]))
	{
		set_io(ex);
		builtin_run(ex, shell);
    	ft_dup_rev(ex);	
		//printf("----- builtin %d. kez------\n", i);
	}
	else
	{
		ex->pid = fork();
		if (ex->pid == 0)
		{
			if(shell->c_pipe - 1 == 0)
			{
				ft_single_exec(shell, i);
				//printf("-----child single %d. kez------\n", i);
			}
			else
			{
				ft_multi_exec(shell, i);
				return (1);
				//printf("-----child multi %d. kez------\n", i);
			}
		}
	}
	return (0);
}
int	ft_perform_dup(int fd, int std_stream)
{
	dup2(fd, std_stream);
	close(fd);
	return (-2);
}

int	exec_handler(t_shell *shell)
{
	int			i;
	//int			status;
	t_exec_node	*exnd;

	i = 0;
	exnd = shell->exec_head;
	if (shell->c_pipe > 1)
		open_pipes(shell);
	while (i < shell->c_pipe)
	{
		if (ft_execve(shell, exnd, i))
			exit(1);
		i++;
		exnd = exnd->next;
	}
	fd_closer(shell);
	wait_al(shell);
	//close_fd(shell->exec_head, i, shell->c_pipe);
	return (0);
}
