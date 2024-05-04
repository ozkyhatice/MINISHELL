#include "../include/minishell.h"

void handler(int signum) {
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	if (argc > 1)
		printf("error in argc");
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(0);
	//printf("%d", getpid());
	initalizer(shell, env);
	free(shell);
	free(shell->cmd2_line);
	free(shell->cmd_line);
	//signal(SIGINT, handler);
	// signal(EOF, handler);
	return(shell->ex_status);
}