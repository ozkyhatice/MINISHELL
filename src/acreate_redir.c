
#include "../include/minishell.h"

t_red    *create_redirection_node(char *str, int type)
{
    t_red *new = malloc(sizeof(t_red));
    if (new)
	{
        new->type = type;
        new->name = ft_strdup (str);
    }
    return (new);
}

void	add_redirection_node(t_shell *shell, char *str, int type)
{
	t_red	*new;

        new = create_redirection_node(str, type);
        if (shell->exec_head->redirection_head == NULL && new)
        {
            new->prev = NULL;
            shell->exec_head->redirection_head = new;
            shell->exec_head->redirection_tail = new;
        }
        else
        {
            new->prev = shell->exec_head->redirection_tail;
            shell->exec_head->redirection_tail->next = new;
            shell->exec_head->redirection_tail = new;
        }
}

void print_redir_node(t_shell *shell)
{
	t_exec_node	*ex;
	t_red		*red;
	int			i;
	int			j;

	ex = shell->exec_head;
	i = 0;
	while (ex)
	{
		j = 0;
		red = ex->redirection_head;
		while (red)
		{
			printf("node#%d	redir#%d	name=%s	type=%d\n", i, j, red->name, red->type);
			red = red->next;
			j++;
		}
		ex = ex->next;
		i++;
	}

}
