#include "../include/minishell.h"

int ft_is_all_digit(char *str)
{
	int i;

	i = 0;
	if(str)
	{
		while(str[i])
		{
			if(!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	
	}return (1);
}

int ft_is_all_alpha(char *str)
{
	int i;

	i = 0;
	if(str)
	{
		while(str[i])
		{
			if(!ft_isalpha(str[i]))
				return (0);
			i++;
		}
	}
	return(1);
	
}

void	run_exit(t_shell *shell, char *str, char *s2)
{
	(void)shell;
	int code;
	//close_all_redirections();
	// ft_free_nodes(shell);
	// ft_free_execnodes(shell);
	// clear_parse_list();
	// clear_command_list();
	if(!str)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if(s2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(" too many arguments\n", 2);
		exit(1);
	}
	else if(ft_is_all_digit(str) || ft_atoi(str) != 0)
	{
		if(ft_atoi(str)==100)
			code = 100;
		else if( ft_atoi(str) == -100)
			code = 156;
		else
			code = ft_atoi(str) % 256;
		exit(code);
	}
	else if(ft_is_all_alpha(str))
	{
		ft_putstr_fd(" numeric argument required", 2);
		exit(255);
	}
	

}