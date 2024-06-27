#include "../include/minishell.h"


static t_subnode *create_parse_node(const char *s)
{
    t_subnode *new = malloc(sizeof(t_subnode));
    if (new) {
        new->word = ft_strdup(s);
        new->next = NULL;
    }
    return (new);
}

void	add_parse_subnode(t_shell *shell, char *s)
{
	t_subnode	*new;

    if (s[0] != '\0' && s)
    {
        new = create_parse_node(s);
        if (shell->subnode_head == NULL && new)
        {
            new->prev = NULL;
            shell->subnode_head = new;
			shell->subnode_tail = new;
        }
        else
        {
            new->prev = shell->subnode_tail;
            shell->subnode_tail->next = new;
            shell->subnode_tail = new;
        }
    }
	
}

void print_subnode(t_shell *shell)
{
    t_subnode *current = shell->subnode_head; 
    printf("\n");
    while (current != NULL) {
        printf("\n%s->\n", current->word);
        current = current->next;
    }
    printf("\n");
}

void ft_free_subnodes(t_shell *shell)
{
    t_subnode *current = shell->subnode_head;
    t_subnode *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    shell->subnode_head = NULL;
    shell->subnode_tail = NULL;
}

char *ft_strjoin_subnode(t_subnode *node)
{
	t_subnode	*current;
	char		*str;
	char		*copy;

	current = node;
	str = NULL;
	while (current)
	{
		if(!str)
			str = current->word;
		else
		{
			copy = ft_strdup(current->word);
			if (copy)
			{
				str = ft_strjoin(str, copy);
				free(copy);
			}
		}	
		current = current->next;
	}
	return (str);
}

