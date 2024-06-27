#include "../include/minishell.h"

void	ft_free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
char	*getcmdpath(char *cmd, char **path)
{
	int		i;
	char	*cmdpath;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		if (access(cmdpath, F_OK) == 0)
		{
			free(tmp);
			return (cmdpath);
		}
		free(tmp);
		free(cmdpath);
		i++;
	}
	return (NULL);
}

void	define_rtype(t_parse_node *node, t_exec_node *exnode)
{
	t_parse_node	*tmp;
	t_exec_node		*ex;

	tmp = node;
	ex = exnode;
	(void)ex;

	while (tmp)
	{
		if(tmp->type == R_REDIR)
			tmp->next->type = OUTPUT;
		else if (tmp->type == APPEND)
			tmp->next->type = APPENDOUT;
		else if (tmp->type == L_REDIR)
			tmp->next->type = INPUT;
		else if (tmp->type == HEREDOC)
			tmp->next->type = HD;
		tmp = tmp->next;
	}
}

t_exec_node	*get_exec_node(t_exec_node *exnode, int indx)
{
	t_exec_node	*tmp;
	int			i;

	i = 0;
	tmp = exnode;
	while (tmp && i < indx)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == indx)
		return (tmp);
	return (NULL);
}

t_parse_node	*get_parse_node(t_parse_node *node, int indx)
{
	t_parse_node	*tmp;
	int				i;

	i = 0;
	tmp = node;
	while (tmp && i < indx)// ls > a
	{
		tmp = tmp->next;
		i++;
	}
	if (i == indx)
		return (tmp);
	return (NULL);
}

void	put_cmnds(t_shell *shell)
{
	int	i;
	int	j;
	int	arg_len;
	t_parse_node	*head;
	t_parse_node	*tmp;
	t_exec_node		*cmnds;

	define_rtype(shell->parse_head, shell->exec_head);
	head = shell->parse_head;
	cmnds = shell->exec_head;
	j = 0;
	while (head)
	{
		i = 0;
		arg_len = 0;
		while (head && head->type != PIPE)
		{
			//printf("\nhead_type= %d head=%s\n", head->type, head->word);
			if (head->type == WORD)
				arg_len++;
			else if(head->type == INPUT || head->type == OUTPUT || head->type == APPENDOUT || head->type == HD)
			{
				if (head->type == APPENDOUT)
					add_redirection_node(shell, head->word, APPENDOUT);
				else if (head->type == INPUT)
					add_redirection_node(shell, head->word, INPUT);
				else if (head->type == OUTPUT)
					add_redirection_node(shell, head->word, OUTPUT);
				else if (head->type == HD)
					add_redirection_node(shell, head->word, HD);	
			}
			head = head->next;
		}
		if (head != NULL)
			head = head->next;
		tmp = get_parse_node(shell->parse_head, j);
		if (tmp != NULL && cmnds != NULL) //&& tmp->type == WORD 
		{
			cmnds->cmd = malloc(sizeof(char *) * (arg_len + 1));
			if(!cmnds->cmd)
				return ;
			while (i < arg_len)
			{
				if (tmp->type == WORD)
				{
					cmnds->cmd[i] = ft_strdup(tmp->word);
					i++;
				}
				j++;
				tmp = tmp->next;
			}
			cmnds->cmd[i] = NULL;
			cmnds = cmnds->next;
		}
	}
	//print_redir_node(shell);
}
