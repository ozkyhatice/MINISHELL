#include "../include/minishell.h"

static t_env	*create_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

int	check_and_update(t_shell *shell, char *name, char *content)
{
	t_env	*tmp;
	char	*tmp_content;

	tmp = shell->env_l;

	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(tmp->name) + 1))
		{
			tmp_content = content;
			tmp->content = ft_strdup(tmp_content);
			if (tmp_content)
				free(tmp_content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_environment(t_shell *shell, char *name, char *content)
{
	t_env	*new;
	t_env	*lst;

	lst = env_lstlast(shell->env_l);
	if (!check_and_update(shell, name, content))
	{
		new = create_env(name, content);
		if (lst->next == NULL)
		{
			lst->next = new;
		// 	shell->env_l = new;
		}
		// else
		// {
		// 	shell->env_l->next = new;
		// 	shell->env_l = shell->env_l->next;
		// }
	}
}

void	add_export(t_shell *shell, char	*arg)
{
	char	**splitted;

	splitted = ft_split(arg, '=');
	if (!splitted[1])
		add_environment(shell, splitted[0], "");
	else
		add_environment(shell, splitted[0], splitted[1]);
	ft_free_arr(splitted);
}

int	run_export(t_exec_node *cmd, t_shell *shell)
{
	t_env	*tmp;
	char	*arg;

	arg = cmd->cmd[1];
	if (!arg)
	{
		tmp = shell->env_l;
		while (tmp && tmp->content)
		{
			printf("declare -x %s", tmp->name);
			if (tmp->content && !is_full_space(tmp->content))
				printf("=\"%s\"", tmp->content);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
		add_export(shell, arg);
	return (1);
}