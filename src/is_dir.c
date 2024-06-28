#include "../include/minishell.h"

void	is_dir(char *path)
{
	struct stat	filestat;
	int				ret;

    ret = stat(path, &filestat);
	if (ret == -1)
	{
		// strerror(errno);
		// perror("ms: ");
		ft_error_msg(path, NULL, E_NOFILE);
		exit(127);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		ft_error_msg(path, NULL, "is a directory");
		exit(126);
	}
	if (ft_access(path))
	{
		ft_error_msg(path, NULL, E_PERM);
		exit(126);
	}
}

void	is_path_ok(char *path, char *cmd, int *ex_status)
{
	if (path == NULL)
	{
		ft_error_msg(cmd, NULL, "command not found");
		*ex_status = 127;
	}
	else if (ft_access(path))	
		ft_error_msg(path, NULL, "not authorize to execute");
}

int ft_access(char *path)
{
    if (access(path, X_OK) != 0)
        return (1);
    return (0);
}
