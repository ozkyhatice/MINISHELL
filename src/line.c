/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:19 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:48:20 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_buffer(char *buf, char **nextline)
{
	char	*temp;

	if (*nextline)
	{
		temp = ft_strjoin(*nextline, buf);
		free(*nextline);
		*nextline = temp;
	}
	else
		*nextline = ft_strdup(buf);
}

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
		ft_buffer(buf, &nextline);
	}
	if (buf)
		free(buf);
	return (nextline);
}

char	*get_line(int fd)
{
	char	*outline;

	outline = NULL;
	if (1 <= 0 || fd < 0)
		return (0);
	outline = buffer(outline, fd);
	if (!(outline))
		return (0);
	return (outline);
}
