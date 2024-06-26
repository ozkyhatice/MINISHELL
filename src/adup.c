#include "../include/minishell.h"

void	add_indx_to_exnd(t_exec_node *exnd)
{
	int	i;

	i = 0;
	while (exnd)
	{
		exnd->id = i;
		i++;
		exnd = exnd->next;
	}
}

void	wait_all(t_exec_node *exnd)
{
	int	status;

	while (exnd)
	{
		waitpid(exnd->pid, &status, 0);
		exnd = exnd->next;
	}
}

void	wait_al(t_shell *shell)
{
	t_exec_node		*ex;
	int				status;

	ex = shell->exec_head;
	while (ex)
	{
		waitpid(ex->pid, &status, 0);
		//shell->exit_code = status / 256;
		// if (ex->outfile == 2 || exec_head->infile == 2)
		// 	shell->exit_code = 1;
		ex = ex->next;
	}
	//g_signal = 0;
}

void	set_dup(t_exec_node *exnd, int i, int count)
{
	t_exec_node	*ex;

	ex = get_exec_node(exnd, i - 1);
	if (i == 0)
		dup2(exnd->fd[1], STDOUT_FILENO);
	else if (i == count - 1)
		dup2(ex->fd[0], STDIN_FILENO);
	else if (exnd->id == i)
	{
		dup2(ex->fd[0], STDIN_FILENO);
		dup2(exnd->fd[1], STDOUT_FILENO);
	}

	
}

void	set_dup2(t_shell *shell, int i)
{
	t_exec_node	*ex;

	ex = get_exec_node(shell->exec_head, i);
	if (ex->in > 0 || ex->out > 0)
		set_io(ex);
	else if (i == 0)
		dup2(shell->fd[i][1], STDOUT_FILENO);
	else if (i == shell->c_pipe - 1)
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
		dup2(shell->fd[i][1], STDOUT_FILENO);
	}
	fd_closer(shell);
}
