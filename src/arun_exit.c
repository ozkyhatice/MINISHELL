#include "../include/minishell.h"

void	run_exit(t_shell *shell)
{
	(void)shell;
	//close_all_redirections();
	// ft_free_nodes(shell);
	// ft_free_execnodes(shell);
	// clear_parse_list();
	// clear_command_list();
	exit(0);
	write(1, "exit\n", 5);
}