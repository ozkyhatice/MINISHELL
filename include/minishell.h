#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# define E_PERM		" Permission denied"
# define E_NOFILE	"No such file or directory"
# define IN_HEREDOC		2
# define AFTER_HEREDOC	3
extern int		g_sig;
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
	OUTPUT,//10
	INPUT,// 11
	APPENDOUT,//12
	HD,//13
	NEWLINE, //14
	NEWLINE_R,//15
};

enum e_builtin
{
	LS = 12,
	ECHO = 13,
	CD = 14,

};

typedef struct s_env
{
	char	*name;
	char	*content;
	struct s_env	*next;
}	t_env;

typedef struct s_red
{
	char	*name;
	int		type;
	struct s_red	*next;
	struct s_red	*prev;
}	t_red;


typedef struct s_parse_node
{
	char				*word;
	enum e_token		type;
	struct s_parse_node	*next;
	struct s_parse_node	*prev;
	char				*heredoc;
}	t_parse_node;

typedef struct	s_subnode
{
	char	*word;
	struct s_subnode	*next;
	struct s_subnode	*prev;
}	t_subnode;

typedef struct s_exec_node
{
	char				**cmd;
	char				*heredoc;
	int					std_in;
	int					std_out;
	int					in;
	int					out;
	int					fd[2];
	pid_t				pid;
	enum e_token		type;
	int					id;
	struct s_red		*redirection_head;
	struct s_red		*redirection_tail;
	struct s_exec_node	*next;
	struct s_exec_node	*prev;
	char			*here_path;

}	t_exec_node;


typedef struct s_shell
{
	char	**path;
	char	**env_p;
	char	*cmd_line;
	char	*skip32;
	char	**commands; //ls -l -a 
	int		er_status;
	int		ex_status;
	int	l_br;
	int	r_br;
	int	br_type;
	int	c_pipe;
	int	**fd;


	//added
	t_parse_node	*parse_head;
	t_parse_node	*parse_tail;
	t_subnode		*subnode_head;
	t_subnode		*subnode_tail;
	t_exec_node		*exec_head;
	t_exec_node		*exec_tail;
	t_env			*env_l;
	bool			arg_mode;

	int				std_in;
	int				std_out;
} t_shell;


//check
int	check_missing_quotes(char *cmd_line);

//is funcs
int	ft_isspace(char c);
int	ft_isquote(char c);
int ft_istoken(char c);
int	ft_exist(char *str, char c);

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

//subnode func
void	add_parse_subnode(t_shell *shell, char *s);
void print_subnode(t_shell *shell);
void ft_free_subnodes(t_shell *shell);

//execnode func
void	add_exec_node(t_shell *shell);
void print_exec_node(t_shell *shell);
void ft_free_execnodes(t_shell *shell);


char *ft_strjoin_subnode(t_subnode *node);



//lexer funcs
int ft_strtoken(char *str);
int	split_char(t_shell *shell, char *str);
void	split_quote(t_shell *shell);
int	split_tokens(char *str, int i);
void	split_dollar(t_shell *shell);

//Syntax
int    syntax_rules(t_shell *shell);
void    bracket_ctrl(t_shell *shell, t_parse_node *tmp);

// dollar kontrol
void	dollar_nullcontrol(t_shell *shell, char *str);
int	dollar_control(char c);
int	dollar_control2(char c, t_shell *shell, char *tmp);
int	special_dollar(char c);

//EXEC
void    counter_pipe(t_shell *shell);
void    create_ex_nodes(t_shell *shell);
void    init_heredoc(t_shell *shell);



char	*get_line(int fd);
void	put_cmnds(t_shell *shell);
void	ft_free_arr(char **str);
t_exec_node	*get_exec_node(t_exec_node *exnode, int indx);
char	*getcmdpath(char *cmd, char **path);
int		exec_handler(t_shell *shell);
int		ft_execve(t_shell *shell, t_exec_node *ex, int i);

void	add_indx_to_exnd(t_exec_node *exnd);
void	wait_all(t_exec_node *exnd);
void	close_fd(t_exec_node *exnd, int i, int count);
void	set_dup(t_exec_node *exnd, int i, int count);
void	open_fd(t_exec_node *exnd);
void	open_pipes(t_shell *shell);
void	fd_closer(t_shell *shell);
void	set_dup2(t_shell *shell, int i);
void	wait_al(t_shell *shell); //senemden

//built-in utils
int	is_full_space(char *rl);

// built-in
int	check_echo_n(char *keyword);
void    builtin_run(t_exec_node *ex, t_shell *shell);
int    is_builtin(char *cmd);
void	run_echo(t_exec_node *ex);
void	run_pwd(void);

//env
void	run_env(t_shell *shell);
void	env_init(t_shell *shell, char **env);
void	run_unset(t_shell *shell);
int		run_export(t_exec_node *cmd, t_shell *shell);
t_env	*env_lstlast(t_env	*lst);

void	run_exit(t_shell *shell, char *str, char *s2);
void	add_environment(t_shell *shell, char *name, char *content);
int	run_cd(t_shell *shell, t_exec_node *cmd);
void	add_redirection_node(t_shell *shell, char *str, int type);
t_red    *create_redirection_node(char *str, int type);

void print_redir_node(t_shell *shell);
void	ft_redirection(t_shell	*shell);
void	ft_error_msg(char *cmd, char *arg, char *msg);
int ft_access(char *path);
void    set_io(t_exec_node *ex);
void    ft_dup_rev(t_exec_node *ex);

void	do_dollar(t_shell *shell, char *str, int *i);
void	quote_remove(t_shell *shell);
void	ft_init_signals(void);
int	control_howmany(char *str, char c);
int	err_msg(char *str);
int	istoken2(char *token);
void	tilda_control(t_shell *shell);

int	ft_check_syntax(char *str);
void	is_path_ok(char *path, char *cmd, int *ex_status);
void	is_dir(char *path);
#endif

