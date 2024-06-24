#include "../include/minishell.h"


static char	*buffer(char *nextline, int fd)
{
	int		countread;
	char	*buf;

	buf = malloc(sizeof(char) * (100));
	if (!buf)
		return (0);
	countread = 1;
	while (countread != 0)
	{
		countread = read(fd, buf, 100);
		if (countread == -1)
		{
			if (nextline)
                free(nextline);
			if (buf)
                free(buf);
			return (0);
		}
		buf[countread] = '\0';
		nextline = ft_strjoin(nextline, buf);
	}
	if (buf)
        free(buf);
	return (nextline);
}

char	*get_line(int fd)
{
	char		*outline;

	outline = NULL;
	if (1 <= 0 || fd < 0)
		return (0);
	outline = buffer(outline, fd);
	if (!(outline))
		return (0);
	return (outline);
}
