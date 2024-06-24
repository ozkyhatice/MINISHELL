#include "../include/minishell.h"

void	ft_fre_arr(char **str)
{
	int	i;

	i = 0;
	if (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
char	*getcmdpath(char *cmd, char **path)
{
	int		i;
	char	*cmdpath;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		if (access(cmdpath, F_OK) == 0)
		{
			free(tmp);
			return (cmdpath);
		}
		free(tmp);
		free(cmdpath);
		i++;
	}
	return (NULL);
}
