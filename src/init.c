#include "../include/minishell.h"

char	**copyenv(char **env)
{
	char	**return_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	return_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		return_env[i] = ft_strdup(env[i]);
	return_env[i] = NULL;
	return (return_env);
}

void	initalizer(t_shell *shell, char **env)
{
	shell->path = ft_split(getenv("PATH"), ':');
	shell->ex_status = 0;
	shell->er_status = 0;
	shell->env_p = copyenv(env);
	printwelcome();
	start_program(shell);
    free(shell->path);
    shell->path = NULL;
    free(shell->env_p);
    shell->env_p = NULL;
}



int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s2 == NULL)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	check_missing_quotes(char *cmd_line)
{
	int	quote;
	int	i;

	quote = 0;
	i = -1;
	while (cmd_line[++i])
	{
		if (quote == 0 && (cmd_line[i] == 34 || cmd_line[i] == 39))
			quote = cmd_line[i];
		else if (quote == cmd_line[i])
			quote = 0;
	}
	return (quote);
}

void	start_program(t_shell *shell)
{
	char *str;
	while (1)
	{
		shell->cmd_line = readline("minishell ~ ");
		if (ft_strcmp(shell->cmd_line, ""))
			add_history(shell->cmd_line);
		else
			free(shell->cmd_line);
		if (check_missing_quotes(shell->cmd_line) != 0)
		{
			perror("Missing quote!\n");
			free(shell->cmd_line);
			free(shell->cmd2_line);
			return ;
		}
		cmd_trim(shell);
		skip_32(shell);
		control_bracket(str);
		parsing(shell);
		// if (!pipe_ctl(shell))segment hatası var
		//  	imp_pipe(shell);
		if (ft_strlen(shell->cmd_line) != 0)
			free(shell->cmd_line);
		// print_parse_node(shell);
		free(str);
		ft_free_nodes(shell);
		// clear_history();
		// system("leaks minishell");
	}
	
}
void	skip_32(t_shell *shell)
{
	int len;
	int i;
	int j;
	int space;
	char *skipped_str;

	len  = ft_strlen(shell->cmd_line);
	i = 0;
	j = 0;
	space = 0;
	while (shell->cmd_line[i] != '\0')
	{
		if (shell->cmd_line[i] == ' ')
			space++;
		i++;
	}
	skipped_str = (char *)malloc(sizeof(char) * (len - space + 1));
	i = 0;
	while (i < (len - space + 1) && (j < len))
	{
		if (shell->cmd_line[j] != ' ')
		{
			skipped_str[i] = shell->cmd_line[j];
			i++;
		}	
		j++;
	}
	skipped_str[i] = '\0'; 
	shell->skip32 = skipped_str;
}

void	imp_pipe(t_shell *shell)
{
	//pipe ve heredoc islenecek
	return ;
}

void	cmd_trim(t_shell *shell)
{
	char	*tmp;

	if (ft_strlen(shell->cmd_line) == 0)
		return ;
	else
	{
		tmp = ft_strdup(shell->cmd_line);
		free(shell->cmd_line);
		shell->cmd_line = ft_strtrim(tmp, " ");
		free(tmp);
	}
}

int	pipe_ctl(t_shell *shell)
{
	int i;
	
	i = -1;
	while (shell->skip32[i++])
	{
		if (shell->skip32[i] == '|')
		{
			if (shell->skip32[i + 1] == '>')
			{
				printf("pipe sonrası >!");
			}
			if (shell->skip32[i - 1] == '>' && i >= 1)
			{
				printf("pipe oncesi >!");
			}
		}
	}
	
	return (0);
}
