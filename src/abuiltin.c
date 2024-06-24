#include "../include/minishell.h"

int    is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return (1);
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd, "cd", 3) == 0)
        return (1);
    // else if (ft_strncmp(cmd, "export", 7) == 0)
    //     return (1);
    // else if (ft_strncmp(cmd, "unset", 6) == 0)
    //     return (1);
    // else if (ft_strncmp(cmd, "env", 4) == 0)
    //     return (1);
    // else if (ft_strncmp(cmd, "exit", 5) == 0)
    //     return (1);
    return (0);
}

int    builtin_run(t_exec_node *ex)
{
    if (ft_strncmp(ex->cmd[0], "echo", 5) == 0)
        return (run_echo(ex));
    else if (ft_strncmp(ex->cmd[0], "pwd", 4) == 0)
        return (run_pwd());
    else if (ft_strncmp(ex->cmd[0], "cd", 3) == 0)
        return (run_cd(ex));
    // else if (ft_strncmp(ex->cmd[0], "export", 7) == 0)
    //     return (run_export(ex));
    // else if (ft_strncmp(ex->cmd[0], "unset", 6) == 0)
    //     return (run_unset(ex));
    // else if (ft_strncmp(ex->cmd[0], "env", 4) == 0)
    //     return (run_env());
    // else if (ft_strncmp(ex->cmd[0], "exit", 5) == 0)
    //     run_exit(0);
    return (0);
}

