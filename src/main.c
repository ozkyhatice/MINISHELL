#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	// int		exit_code;

	if (argc > 1)
	{
		printf("minishell: %s: No such file or directory", argv[1]);
		return (127);
	}
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(0);
	ft_init_signals();
	initalizer(shell, env);
	//exit_code = shell->ex_status;
	// free(shell->cmd_line);
	// free(shell);
	return(0);
}
