#include "../include/minishell.h"

static	char *ft_strjoin_subnode(t_subnode *node)
{
	t_subnode	*current;
	char		*str;

	current = node;
	str = NULL;
	while (current)
	{
		if(!str)
			str = current->word;
		else
			str = ft_strjoin(str, current->word);
		current = current->next;
	}
	return (str);
}

void	quote_dollar(t_shell *shell, char *word, int *i)
{
	int	s;
	char	*str;
	char	*env_value;
	char	*tmp;

	*i += 1;
	add_parse_subnode(shell, "\"");
	while (word[*i] && word[*i] != '\"')
	{
		
		if (word[*i] == '$')
		{
			*i += 1;
			s = *i;
			while (word[*i] && word[*i] != '$' && word[*i] != '\"' && word[*i] != ' ')
				*i += 1;
			str = ft_substr(word, s, *i - s);
			if (str)
			{
				env_value = getenv(str);
				if (env_value)
				{
					tmp = ft_strdup(env_value);
					if (tmp)
					{
						add_parse_subnode(shell, tmp);
						free(tmp);
					}
				}
			}
			if (str)
				free(str);
			
		}
		else if (word[*i] != '$')
		{
			s = *i;
			while (word[*i] && word[*i] != '$' && word[*i] != '\"')
				*i += 1;
			str = ft_substr(word, s, *i - s);
			add_parse_subnode(shell, str);
			if (str)
				free(str);
			
		}
		*i += 1;
	}
	if (word[*i - 1])
		add_parse_subnode(shell, "\"");

}
static char	*parse_dollar(t_shell *shell, char *word)
{

	int	i;
	int	s;
	char		*tmp_str;
	char		*tmp;
	char		*env_value;

	i = 0;
	tmp_str = NULL;
	while (word[i])
	{
		//çift tırnak görürse çift tırnak bitene kadar devam edicek
		//dolar görürse boşluk veya dolara kadar devam edicek
		if (word[i] == '\"')
		{
			quote_dollar(shell, word, &i);
		}
		else if (word[i] == '$')
		{
			i++;
			s = i;
			while(word[i] && word[i] != ' ' && word[i] != '$' && word[i] != '\"')
				i++;
			if (tmp_str)
				free(tmp_str);
			tmp_str = ft_substr(word, s, i - s);
			if (tmp_str)
			{
				env_value = getenv(tmp_str);
				if (env_value)
				{
					tmp = ft_strdup(env_value);
					if (tmp)
					{
						add_parse_subnode(shell, tmp);
						free(tmp);
					}
				}
			}

		}
		// else if (word[i] == '\"')
		// {
			
		// }
		else
		{
			s = i;
			while (word[i] && word[i] != '$' && word[i] != '\"')
				i++;
			if (tmp_str)
				free(tmp_str);
			tmp_str = ft_substr(word, s, i - s);
			if (tmp_str)
				add_parse_subnode(shell, tmp_str);
		}
	}
	free(tmp_str);
	tmp_str = ft_strjoin_subnode(shell->subnode_head);
	ft_free_subnodes(shell);
	return (tmp_str);
}


void	split_dollar(t_shell *shell)
{
	t_parse_node	*node;
	char			*mal;

	node = shell->parse_head;
	while (node)
	{
		if (ft_isdollar(node->word))
		{	
			mal = ft_strdup(node->word);
			if (node->word)
				free(node->word);
			node->word = parse_dollar(shell, mal);
			free(mal);
		}
		node = node->next;
	}
}