#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/history.h>

enum e_token
{
	AND,//0
	OR,//1
	PIPE,//2
	L_REDIR,//3
	R_REDIR,//4
	HEREDOC,//5
	APPEND,//6
	L_BRACKET,//7
	R_BRACKET,//8
	WORD,//9
};

typedef struct s_parse_node
{
	char				*word;
	enum e_token		type;
	struct s_parse_node	*next;
	struct s_parse_node	*prev;
}	t_parse_node;

typedef struct s_shell{

	char	**path;
	char	**env_p;
	char	*cmd_line;
	char	*cmd2_line;
	char	*skip32;
	int		er_status;
	int		ex_status;

	//added
	t_parse_node	*parse_head;
	t_parse_node	*parse_tail;
	bool			arg_mode;

} t_shell;


//check
int	check_missing_quotes(char *cmd_line);

//is funcs
int	ft_isspace(char c);
int	ft_isquote(char c);
int ft_istoken(char c);

//others
void	initalizer(t_shell *shell, char **env);
void	printwelcome(void);
void	start_program(t_shell *shell);

//token func
enum e_token get_token(const char *str);
enum e_token char_token(const char *str);
//token utils
int same_str(const char *str1, char *str2);
int	ft_strcmp(char *s1, char *s2);

//node funcs
void	add_parse_node(t_shell *shell, char *s);
void print_parse_node(t_shell *shell);
void ft_free_nodes(t_shell *shell);

//lexer funcs
int ft_strtoken(char *str);
int	split_char(t_shell *shell, char *str);
void	split_quote(t_shell *shell);
int	split_tokens(char *str, int i);

//Syntax
int    syntax_rules(t_shell *shell);

#endif