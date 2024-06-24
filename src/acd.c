#include "../include/minishell.h"

//extern	t_shell	*shell;

int	go_dir(t_shell *shell, char *path, char **new)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("directory not changed\n");
		free(pwd);
		free(oldpwd);
		return (0);
	}
	*new = getcwd(NULL, 0);
	add_environment(shell, "PWD", *new);
	add_environment(shell, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return (1);
}

int	cd_exec(t_shell *shell, t_exec_node **ex, char **home, char **tmp, char **new)
{
	int	res;

	res = -1;
	if ((*ex)->cmd[1] == NULL)
	{
		res = go_dir(shell, *home, new);
		if (res == 0)
		{
			free(*home);
			return (0);
		}
		*tmp = *home;
	}
	else
	{
		res = go_dir(shell, (*ex)->cmd[1], new);
		if (res == 0)
		{
			printf("cd: %s: No such file or directory\n", (*ex)->cmd[1]);
			free(*home);
			return (0);
		}
		*tmp = (*ex)->cmd[1];
	}
	return (1);
}

int	run_cd(t_shell *shell, t_exec_node *ex)
{
	char	*home;
	char	*curr;
	char	*tmp;
	char	*new;
	int		res;

	res = -1;
	home = getenv("HOME");
	printf("home: %s\n", home);
	curr = getenv("PWD");
	res = cd_exec(shell, &ex, &home, &tmp, &new);
	if (!res)
		return (0);
	add_environment(shell, "PWD", new);
	add_environment(shell, "OLDPWD", curr);
	free(new);
	free(curr);
	free(home);
	return (1);
}