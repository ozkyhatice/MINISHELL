#include "../include/minishell.h"

static t_exec_node *create_exec_node()
{
    t_exec_node *new = malloc(sizeof(t_exec_node));
    if (new)
	{
        new->type = -1;
        new->cmd = NULL;
        new->heredoc = NULL;
        new->next = NULL;
        new->pid = -1;
        new->in = 0;
        new->out = 1;
    }
    return (new);
}

void	add_exec_node(t_shell *shell)
{
	t_exec_node	*new;

    
        new = create_exec_node();
        if (shell->exec_head == NULL && new)
        {
            new->prev = NULL;
            shell->exec_head = new;
            shell->exec_tail = new;
        }
        else
        {
            new->prev = shell->exec_tail;
            shell->exec_tail->next = new;
            shell->exec_tail = new;
        }
    
	
}

void print_exec_node(t_shell *shell)
{
    t_exec_node *current = shell->exec_head; 
    //printf("\n");
	int j = 0;
    while (current != NULL)
	{
		int	i = 0;
        //printf("pid:%d komut=%s: type: %u\n",current->pid, current->cmd[i], current->type);
		while (current->cmd[i] != NULL)
		{
			printf("node#%d	komut#%s\n", j, current->cmd[i]);
			i++;
		}
        current = current->next;
		j++;
    }
    //printf("\n");
}

void ft_free_execnodes(t_shell *shell)
{
    t_exec_node *current = shell->exec_head;
    t_exec_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->heredoc);
        ft_free_arr(current->cmd);
        free(current);
        
        current = next;
    }
    shell->exec_head = NULL;
    shell->exec_tail = NULL;
}


