#include "../include/minishell.h"

void    counter_pipe(t_shell *shell)
{
    t_parse_node	*node;
	
    shell->c_pipe = 0;
	node = shell->parse_head;
    while (node)
    {
        if (node->type == PIPE)
            shell->c_pipe++;
        node = node->next;
    }
    shell->c_pipe++;
    create_ex_nodes(shell);
    // printf("pipe: %d\n", shell->c_pipe);
    // print_exec_node(shell);
}

void    create_ex_nodes(t_shell *shell)
{
    int i;

    i = 0;
    while (i < shell->c_pipe)
    {
        add_exec_node(shell);
        i++;
    }
    //printf("i:%d", i);
}