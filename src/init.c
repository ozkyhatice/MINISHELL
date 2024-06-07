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

// char	*skip_32(t_shell *shell)
// {
// 	int len;
// 	int i;
// 	int j;
// 	int space;
// 	char *skipped_str;

// 	len  = ft_strlen(shell->cmd_line);
// 	i = 0;
// 	j = 0;
// 	space = 0;
// 	while (shell->cmd_line[i] != '\0')
// 	{
// 		if (shell->cmd_line[i] == ' ')
// 			space++;
// 		i++;
// 	}
// 	skipped_str = (char *)malloc(sizeof(char) * (len - space + 1));
// 	i = 0;
// 	while (i < (len - space + 1) && (j < len))
// 	{
// 		if (shell->cmd_line[j] != ' ')
// 		{
// 			skipped_str[i] = shell->cmd_line[j];
// 			i++;
// 		}	
// 		j++;
// 	}
// 	skipped_str[i] = '\0'; 
// 	return (skipped_str);
// }

void	initalizer(t_shell *shell, char **env)
{
	shell->path = ft_split(getenv("PATH"), ':');
	shell->ex_status = 0;
	shell->er_status = 0;
	shell->env_p = copyenv(env);
	shell->parse_head = NULL;
	shell->parse_tail = NULL;
	shell->subnode_head = NULL;
	shell->exec_head = NULL;
	shell->exec_tail = NULL;
	printwelcome();
	start_program(shell);
    free(shell->path);
    shell->path = NULL;
    free(shell->env_p);
    shell->env_p = NULL;
}

void	start_program(t_shell *shell)
{
	//char	*str;
	while (1)
	{
		shell->l_br = 0;
		shell->r_br = 0;
		shell->cmd_line = readline("\033[0;31m(minishell)~\033[0m ");
		if (ft_strcmp(shell->cmd_line, ""))	//if (shell->cmd_line[0] != '\0')
			add_history(shell->cmd_line);
		else
			free(shell->cmd_line);
		if (check_missing_quotes(shell->cmd_line) != 0)
			printf("Missing quote!\n");
		else
		{
			split_quote(shell);
			syntax_rules(shell);
			split_dollar(shell);
			counter_pipe(shell);
			//init_heredoc(shell);
			print_parse_node(shell);
			
			//printf("buraya geldik -> putcmds\n");
			put_cmnds(shell);
			//printf("buraya geldik -> putcmds yapıldı\n");
			print_exec_node(shell);
		}
		//str = skip_32(shell);
		//printf("%s\n", str);
		//control_bracket(str);
		// parsing(shell);
		// if (!pipe_ctl(shell))segment hatası var
		//  	imp_pipe(shell);
		if (ft_strlen(shell->cmd_line) != 0)
			free(shell->cmd_line);
		ft_free_nodes(shell);
		ft_free_execnodes(shell);
		// clear_history();
		// system("leaks minishell");
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
