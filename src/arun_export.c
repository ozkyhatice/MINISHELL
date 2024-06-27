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

	tmp = shell->env_l;

	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
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

	if (!check_and_update(shell, name, content))
	{
		new = create_env(name, content);
		lst = env_lstlast(shell->env_l);
		if (lst == NULL)
		{
			shell->env_l = new;
		}
		else
		{
			lst->next = new;
		}
	}
}

void	add_export(t_shell *shell, char *arg)
{
	char	**splitted;

	splitted = ft_split(arg, '=');
	if (ft_check_syntax(splitted[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		shell->ex_status = 1;
		ft_free_arr(splitted);
		return;
	}
	if (!splitted[1])
		add_environment(shell, splitted[0], "");
	else
		add_environment(shell, splitted[0], splitted[1]);
	ft_free_arr(splitted);
}

int	ft_is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_isname(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_check_syntax(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isname(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	run_export(t_exec_node *cmd, t_shell *shell)
{
	t_env	*tmp;
	char	*arg;

	if (!cmd->cmd[1])
	{
		tmp = shell->env_l;
		while (tmp)
		{
			printf("declare -x %s", tmp->name);
			if (tmp->content && !is_full_space(tmp->content))
				printf("=\"%s\"", tmp->content);
			printf("\n");
			tmp = tmp->next;
		}
		return (1);
	}

	for (int i = 1; cmd->cmd[i]; i++)
	{
		arg = cmd->cmd[i];
		if (ft_strchr(arg, '=') != NULL)
		{
			add_export(shell, arg);
		}
		else if (ft_check_syntax(arg))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->ex_status = 1;
		}
		else
		{
			add_environment(shell, arg, "");
		}
	}
	return (1);
}
