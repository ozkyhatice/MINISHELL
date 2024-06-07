#include "../include/minishell.h"

static void	env_dollar(t_shell *shell, char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (tmp)
	{
		add_parse_subnode(shell, tmp);
		free(tmp);
	}
}

static void	add_dollar(t_shell *shell,  char *str)
{
	char	*tmp;
	char	*dollar;
	char	*join;

	tmp = ft_strdup(str);
	dollar = ft_strdup("$");
	if (tmp)
	{
		join = ft_strjoin(dollar, tmp);
		add_parse_subnode(shell, join);
		free(tmp);
		free(dollar);
		free(join);
	}
}

static void	do_dollar(t_shell *shell, char *str, int *i)
{
	char	*word;
	char	*tmp;
	char	*env_value;
	int		s;

	word = str;
	tmp = NULL;
	env_value = NULL;
	*i = *i + 1;
	s = *i;
	while(word[*i] && word[*i] != ' ' && word[*i] != '$' && word[*i] != '\"')
		*i = *i + 1;
	if (tmp)
		free(tmp);
	tmp = ft_substr(word, s, *i - s);
	if (tmp)
	{
		env_value = getenv(tmp);
		printf("%s\n", env_value);
		if (env_value)
			env_dollar(shell, env_value);
		else if ((tmp[0] >= '1' && tmp[0] <= '9') ||
			tmp[0] == '*' || tmp[0] == '@' || tmp[0] == '!')
				dollar_nullcontrol(shell, tmp);
		else
		{
			if (dollar_control(tmp[0]))
				add_dollar(shell, tmp);
			if (dollar_control2(tmp[0], shell, tmp))
				add_parse_subnode(shell, "error");
		}
		free(tmp);
	}
}

static void	quote_dollar(t_shell *shell, char *word, int *i)
{
	int	s;
	char	*str;
	// char	*env_value;
	//char	*tmp;

	*i += 1;
	str = NULL;
	//add_parse_subnode(shell, "\""); //FREELENİCEK 
	while (word[*i] && word[*i] != '\"')
	{
		
		if (word[*i] == '$')
		{
			do_dollar(shell, word, i);
			//  *i += 1;
			//  s = *i;
			// while (word[*i] && word[*i] != '$' && word[*i] != '\"' && word[*i] != ' ')
			// 	*i += 1;
			// str = ft_substr(word, s, *i - s);
			// if (str)
			// {
			// 	env_value = getenv(str);
			// 	if (env_value)
			// 	{
			// 		tmp = ft_strdup(env_value);
			// 		if (tmp)
			// 		{
			// 			add_parse_subnode(shell, tmp);
			// 			free(tmp);
			// 		}
			// 	}
			// 	free(str);
			// }			
		}
		else
		{
			s = *i;
			while (word[*i] && word[*i] != '$' && word[*i] != '\"')
				*i += 1;
			if (str)
				free(str);
			str = ft_substr(word, s, *i - s);
			if (str)
			{
				add_parse_subnode(shell, str);
				free(str);
			}
		}
		
	}
}


static char	*parse_dollar(t_shell *shell, char *word)
{

	int	i;
	int	s;
	char		*tmp_str;

	i = 0;
	tmp_str = NULL;
	while (word[i])
	{
		if (word[i] == '\"')
			quote_dollar(shell, word, &i);
		else if (word[i] == '$')
			do_dollar(shell, word, &i);
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
	tmp_str = ft_strjoin_subnode(shell->subnode_head);
	//printf("%s\n", tmp_str);
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
		if (ft_exist(node->word, '$'))
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