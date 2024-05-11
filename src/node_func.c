#include "../include/minishell.h"

static t_parse_node *create_parse_node(const char *s)
{
    t_parse_node *new = malloc(sizeof(t_parse_node));
    if (new) {
        new->type = get_token(s);
        new->word = ft_strdup(s);
        new->next = NULL;
    }
    return (new);
}

void	add_parse_node(t_shell *shell, char *s)
{
	t_parse_node	*new;

    if (s[0] != '\0' && s)
    {
        new = create_parse_node(s);
        if (shell->parse_head == NULL && new)
        {
            new->prev = NULL;
            shell->parse_head = new;
            shell->parse_tail = new;
        }
        else
        {
            new->prev = shell->parse_tail;
            shell->parse_tail->next = new;
            shell->parse_tail = new;
        }
    }
	
}

void print_parse_node(t_shell *shell)
{
    t_parse_node *current = shell->parse_head; 
    printf("\n");
    while (current != NULL) {
        printf("%s->", current->word);
        current = current->next;
    }
    printf("\n");
}

void ft_free_nodes(t_shell *shell)
{
    t_parse_node *current = shell->parse_head;
    t_parse_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
    shell->parse_head = NULL;
    shell->parse_tail = NULL;
}
