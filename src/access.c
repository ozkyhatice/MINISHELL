#include "../include/minishell.h"

int ft_access(char *path)
{
    if (access(path, X_OK) != 0)
    {
        return (1);
    }
    return (0);
}
