#include "../include/minishell.h"

static int err_msg(char *c)
{
    printf("bash: syntax error near unexpected token `%s'\n", c);
        return (0);
}
static  int istoken2(char *token)
{
    if (!ft_strncmp(token, "|", ft_strlen(token)))
        return (1);
    else if (!ft_strncmp(token, ">", ft_strlen(token)))
        return (1);
    else if (!ft_strncmp(token, "<", ft_strlen(token)))
        return (1);
    else
        return (0);
}

static int    pipe_control(t_parse_node	*parse_head)
{
    t_parse_node    *tmp_node;

    tmp_node = parse_head;
    while (tmp_node)
    {
        if (parse_head->type == PIPE)
            return (err_msg("|"));
        else if (tmp_node->type == PIPE && tmp_node->next == NULL)
            return(err_msg("|"));
        else if (tmp_node->next && tmp_node->next->type == PIPE && istoken2(tmp_node->word))
            return(err_msg("|"));
        tmp_node = tmp_node -> next;
    }
    return (1);
}

static int    redirection_control(t_parse_node	*parse_head)
{
    // t_parse_node    *tmp_node;

    // tmp_node = parse_head;
    // while (tmp_node)
    // {
    //     if ()
    //         return(err_msg("newline"));
    //     tmp_node = tmp_node -> next;
    // }
    return (1);
}


int    syntax_rules(t_shell *shell)
{
    if (!pipe_control(shell->parse_head))
        return (-1);
    if (!redirection_control(shell->parse_head))
        return (-1);
    return (0);
}