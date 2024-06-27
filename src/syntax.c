#include "../include/minishell.h"

static int	control_rules(t_shell *shell, t_parse_node *tmp_node)
{
	if (shell->parse_head->type == PIPE)
		return (err_msg("|"));
	else if (shell->parse_head->word[0] == '|'
		&& shell->parse_head->word[1] == '|')
		return (err_msg("||"));
	else if (tmp_node->next && tmp_node->type == L_BRACKET
		&& tmp_node->next->type == R_BRACKET)
		return (err_msg("("));
	else if (tmp_node->next && tmp_node->type == R_BRACKET
		&& tmp_node->next->type == L_BRACKET)
		return (err_msg(")"));
	else if (tmp_node->next && tmp_node->type == PIPE
		&& tmp_node->next->type == PIPE)
		return (err_msg("|"));
	else if (tmp_node->next && tmp_node->type == L_REDIR
		&& tmp_node->next->type == L_REDIR)
		return (err_msg("<"));
	else if (tmp_node->next && tmp_node->type == R_REDIR
		&& tmp_node->next->type == R_REDIR)
		return (err_msg(">"));
	else
		return (0);
}

int	control_rules2(t_shell *shell, t_parse_node *tmp_node)
{
	if (tmp_node->next && tmp_node->next->next && tmp_node->next->type == PIPE
		&& (tmp_node->next->next->type == L_REDIR
			|| tmp_node->next->next->type == R_REDIR)
		&& istoken2(tmp_node->word))
		return (err_msg(tmp_node->next->next->word));
	else if (tmp_node->next && tmp_node->next->type == PIPE
		&& istoken2(tmp_node->word))
		return (err_msg("newline"));
	else if ((tmp_node->type == L_REDIR || tmp_node->type == APPEND
			|| tmp_node->type == R_REDIR || tmp_node->type == HEREDOC
			|| tmp_node->type == NEWLINE)
		&& !tmp_node->next)
		return (err_msg("newline"));
	if (shell->r_br > shell->l_br)
		return (err_msg(")"));
	else
		return (0);
}

int	control_rules3(t_parse_node *tmp_node)
{
	if (tmp_node->next && (tmp_node->next->type == R_REDIR
			|| tmp_node->next->type == L_REDIR
			|| tmp_node->next->type == APPEND
			|| tmp_node->next->type == HEREDOC
			|| tmp_node->next->type == NEWLINE)
		&& (tmp_node->type == R_REDIR
			|| tmp_node->type == L_REDIR
			|| tmp_node->type == APPEND
			|| tmp_node->type == HEREDOC
			|| tmp_node->type == NEWLINE))
		return (err_msg(tmp_node->next->word));
	else
		return (0);
}

int	syntax_rules(t_shell *shell)
{
	t_parse_node	*tmp_node;
	int				er_code;

	tmp_node = shell->parse_head;
	er_code = 0;
	while (tmp_node)
	{
		bracket_ctrl(shell, tmp_node);
		if (er_code == 0)
			er_code = control_howmany(tmp_node->word, '|');
		if (er_code == 0)
			er_code = control_howmany(tmp_node->word, '<');
		if (er_code == 0)
			er_code = control_howmany(tmp_node->word, '>');
		if (er_code == 0)
			er_code = control_rules(shell, tmp_node);
		if (er_code == 0)
			er_code = control_rules2(shell, tmp_node);
		if (er_code == 0)
			er_code = control_rules3(tmp_node);
		tmp_node = tmp_node -> next;
	}
	if (shell->l_br < shell->r_br)
		return (err_msg(")"));
	return (er_code);
}
