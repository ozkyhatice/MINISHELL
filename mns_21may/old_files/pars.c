#include "../include/minishell.h"

void parsing(t_shell *shell)
{
    int f;
    int i;

    i = 0;
    while (shell->cmd_line && shell->cmd_line[i])
    {
        while (shell->cmd_line[i] && shell->cmd_line[i] <= 32 && shell->cmd_line[i] >= 0)
            i++;
        f = i;
        while (shell->cmd_line[i] && shell->cmd_line[i] > 32)
            i++;
        if (f < i)
        {
            add_parse_node(shell, ft_substr(shell->cmd_line, f, i - f));
        }
    }
}