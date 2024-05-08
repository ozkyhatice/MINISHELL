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

int    syntax_rules(t_shell *shell)
{
    
    t_parse_node    *tmp_node;

    tmp_node = shell->parse_head;

    while (tmp_node)
    {
        if (shell->parse_head->type == PIPE)
            return (err_msg("|"));
        if (tmp_node->next && tmp_node->next->type == PIPE && istoken2(tmp_node->word))
            return(err_msg("|"));
        if (tmp_node->type >= 3 && tmp_node->type <= 6 && !tmp_node->next)
            return(err_msg("newline"));
        if (tmp_node->next && tmp_node->type == L_BRACKET && tmp_node->next->type == R_BRACKET)
            return(err_msg("("));
        if (tmp_node->next && tmp_node->type == R_BRACKET && tmp_node->next->type == L_BRACKET)
            return(err_msg(")"));
        tmp_node = tmp_node -> next;
    }
    return (0);
}