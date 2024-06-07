#include "../include/minishell.h"

void handler(int signum)
{
	(void)signum;
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	t_shell	*shell;
	if (argc > 1)
		printf("error in argc");
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(0);
	//printf("%d", getpid());
	initalizer(shell, env);
	free(shell->cmd_line);
	free(shell);

	//signal(SIGINT, handler);
	// signal(EOF, handler);
	return(0);
}
