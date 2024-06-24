#include "../include/minishell.h"

void    bracket_ctrl(t_shell *shell, t_parse_node *tmp)
{
    int i;

    i = 0;
    while (tmp->word[i]) // env icinde parantez verince burdan gecmemesi icin
    {
        if (tmp->word[i] == '(')
        {
            shell->br_type = L_BRACKET;
            shell->l_br++;
        }
        if (tmp->word[i] == ')')
        {
            shell->r_br++;
            shell->br_type = R_BRACKET;
        }
        i++;
    }
}

// void   control_redir(shell)
// {
//     t_parse_node    *tmp_node;

//     tmp_node = shell->parse_head;
//     while (tmp_node)
//     {
//         if (tmp_node->next && tmp_node->type == L_REDIR && tmp_node->next->type == L_REDIR)
//             return (err_msg("<"));
//         if (tmp_node->next && tmp_node->type == R_REDIR && tmp_node->next->type == R_REDIR)
//             return (err_msg(">"));
//     }
// }
