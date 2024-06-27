#include <unistd.h>
#include <stdio.h>

int    pipe_ctl(char *str)
{
    int i;

    i = -1;

    while (str[++i]);
    if (str[--i] == '|' || str[i] == '>' || str[i] == '<')
    {
        while (str[--i])
        {
            if (str[i + 1] == '|' && (str[i] == '>' || str[i] == '<'))
            {
                printf("Minishell: syntax error near unexpected token `|'\n");
                
                return (1);
            }
            else if ((str[i] == '>' || str[i] == '<') && (str[i - 1] == '|'))
            {
                printf("Minishell: syntax error near unexpected token `|'\n");
                
                return (1);
            }
            else if (str[i] != ' ')
                break ;
        }
    }
    return (0);
}
int main()
{
  char *s="ls-l|<";
  pipe_ctl("ls-l<|");
  return 0;
}

int	pipe_ctl(t_shell *shell, char *str)
{
	int i;

	i = -1;

	while (str[++i]);
	if (str[--i] == '|' || str[i] == '>' || str[i] == '<')
	{
		while (str[--i])
		{
			if (str[i + 1] == '|' && (str[i] == '>' || str[i] == '<'))
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				shell->ex_status = 1;
				return (1);
			}
			else if ((str[i] == '>' || str[i] == '<') && (str[i - 1] == '|'))
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				shell->ex_status = 1;
				return (1);
			}
			else if (str[i] != ' ')
				break ;
		}
	}
	return (0);
}

//ls ||>
// ls <||
// ls -la <| asd