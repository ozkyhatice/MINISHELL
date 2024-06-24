#include "../include/minishell.h"

void	ft_single_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	exnd = get_exec_node(shell->exec_head, i);
	path = getcmdpath(exnd->cmd[i], shell->path);
	if (execve(path, exnd->cmd, NULL) == -1)
	{
		if (!path)
			printf("command not found\n");
		else
			printf("execve çalışamadı\n");
	}
}

void	ft_multi_exec(t_shell *shell, int i)
{
	t_exec_node	*exnd;
	char		*path;

	exnd = get_exec_node(shell->exec_head, i);
	path = getcmdpath(exnd->cmd[0], shell->path);
	set_dup2(shell, i);
	//close_fd(shell->exec_head, i, shell->c_pipe);
	//printf("-------path: %s komut: %s----------\n", path, exnd->cmd[i]);
	if (execve(path, exnd->cmd, NULL) == -1)
	{
		printf("execve çalışamadı\n");
		printf("path: %s\n komut: %s\n", path, exnd->cmd[0]);
	}
}

void	ft_execve(t_shell *shell, t_exec_node *ex, int i)
{
	if (shell->c_pipe == 1 && is_builtin(ex->cmd[0]))
	{
		builtin_run(ex, shell);
		printf("-----child builtin %d. kez------\n", i);
		builtin_run(ex, shell);
	}
	else
	{
		ex->pid = fork();
		if (ex->pid == 0)
		{
			if(shell->c_pipe - 1 == 0)
			{
				ft_single_exec(shell, i);
				printf("-----child single %d. kez------\n", i);

			}
			else
			{
				ft_multi_exec(shell, i);
				printf("-----child multi %d. kez------\n", i);
			}
		}
	}
	
}


void	exec_handler(t_shell *shell)
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
		ft_execve(shell, exnd, i);
		i++;
		exnd = exnd->next;
	}
	fd_closer(shell);
	wait_al(shell);
	//close_fd(shell->exec_head, i, shell->c_pipe);

}
