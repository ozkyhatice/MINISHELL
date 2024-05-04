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

// enum KeyCodes {
// 	STRING = 0,
//     FILE = 1,
// 	PIPE = 2,
// };

enum e_token
{
	AND,
	OR,
	PIPE,
	L_REDIR,
	R_REDIR,
	HEREDOC,
	APPEND,
	L_BRACKET,
	R_BRACKET,
	WORD,
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

void	initalizer(t_shell *shell, char **env);
void	parsing(t_shell *shell);
void	printwelcome(void);
void	start_program(t_shell *shell);
void	cmd_trim(t_shell *shell);
int	pipe_ctl(t_shell *shell);
void	imp_pipe(t_shell *shell);


enum e_token get_token(const char *str);
enum e_token char_token(const char *str);


//son eklenilenler
int					parse(t_shell *shell);
void				print_parse_node(t_shell *shell);
void				add_parse_node(t_shell *shell, char *s);
static t_parse_node	*create_parse_node(const char *s);
void				ft_free_nodes(t_shell *shell);
int same_str(const char *str1, char *str2);
void control_bracket(const char *str);
int bracket_counter(const char *str, char c);
void	skip_32(t_shell *shell);
#endif