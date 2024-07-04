/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdemir <akdemir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:52:23 by akdemir           #+#    #+#             */
/*   Updated: 2024/07/04 13:52:24 by akdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/ioctl.h>
# include <sys/stat.h>
# define E_PERM		" Permission denied"
# define E_NOFILE	"No such file or directory"
# define IN_HEREDOC		2
# define AFTER_HEREDOC	3
# define IN_CMD		4
# define AFTER_CMD	5

int		g_sig;

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
	NEWLINE_N, //14
	NEWLINE_N_R,//15
};

enum e_builtin
{
	LS = 12,
	ECHO = 13,
	CD = 14,
};

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_red
{
	char			*name;
	int				type;
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

typedef struct s_subnode
{
	char				*word;
	struct s_subnode	*next;
	struct s_subnode	*prev;
}	t_subnode;

typedef struct s_put_cmd
{
	int					i;
	int					j;
	int					arg_len;
	t_parse_node		*head;
	t_parse_node		*tmp;
	struct s_exec_node	*cmnds;
}	t_put_cmd;

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
	int					ex_flag;
	struct s_red		*redirection_head;
	struct s_red		*redirection_tail;
	struct s_exec_node	*next;
	struct s_exec_node	*prev;
	char				*here_path;

}	t_exec_node;

typedef struct s_shell
{
	char			**path;
	char			**env_p;
	char			*cmd_line;
	char			*skip32;
	char			**commands;
	char			**env;
	int				er_status;
	int				ex_status;
	int				ex_ex_status;
	int				l_br;
	int				r_br;
	int				br_type;
	int				c_pipe;
	int				redir_flag;
	int				**fd;
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
}	t_shell;

//check
int				check_missing_quotes(char *cmd_line);

//is funcs
int				ft_isspace(char c);
int				ft_isquote(char c);
int				ft_istoken(char c);
int				ft_exist(char *str, char c);

//others
void			initalizer(t_shell *shell, char **env);
void			printwelcome(void);
void			start_program(t_shell *shell);

//token func
enum e_token	get_token(const char *str);
enum e_token	char_token(const char *str);
//token utils
int				same_str(const char *str1, char *str2);
int				ft_strcmp(char *s1, char *s2);

//node funcs
void			add_parse_node(t_shell *shell, char *s);
void			print_parse_node(t_shell *shell);
void			ft_free_nodes(t_shell *shell);

//subnode func
void			add_parse_subnode(t_shell *shell, char *s);
void			print_subnode(t_shell *shell);
void			ft_free_subnodes(t_shell *shell);

//execnode func
void			add_exec_node(t_shell *shell);
void			print_exec_node(t_shell *shell);
void			ft_free_execnodes(t_shell *shell);

char			*ft_strjoin_subnode(t_subnode *node);

//lexer funcs
int				ft_strtoken(char *str);
int				split_char(t_shell *shell, char *str);
void			split_quote(t_shell *shell);
int				split_tokens(char *str, int i);
void			split_dollar(t_shell *shell);

//Syntax
int				syntax_rules(t_shell *shell);
void			bracket_ctrl(t_shell *shell, t_parse_node *tmp);

// dollar kontrol
void			dollar_nullcontrol(t_shell *shell, char *str);
int				dollar_control(char c);
int				dollar_control2(char c, t_shell *shell, char *tmp);
int				special_dollar(char c);

//EXEC
void			counter_pipe(t_shell *shell);
void			create_ex_nodes(t_shell *shell);
void			init_heredoc(t_shell *shell);

char			*get_line(int fd);
void			put_cmnds(t_shell *shell);
void			ft_free_arr(char **str);
t_exec_node		*get_exec_node(t_exec_node *exnode, int indx);
char			*getcmdpath(char *cmd, char **path, t_env *env);
int				exec_handler(t_shell *shell);
int				ft_execve(t_shell *shell, t_exec_node *ex, int i);

void			add_indx_to_exnd(t_exec_node *exnd);
void			wait_all(t_exec_node *exnd);
void			close_fd(t_exec_node *exnd, int i, int count);
void			set_dup(t_exec_node *exnd, int i, int count);
void			open_fd(t_exec_node *exnd);
void			open_pipes(t_shell *shell);
void			fd_closer(t_shell *shell);
void			set_dup2(t_shell *shell, int i);
void			wait_al(t_shell *shell); //senemden

//built-in utils
int				is_full_space(char *rl);

// built-in
int				check_echo_n(char *keyword);
void			builtin_run(t_exec_node *ex, t_shell *shell);
int				is_builtin(char *cmd);
void			run_echo(t_exec_node *ex, t_shell *shell);
void			run_pwd(void);

//env
void			run_env(t_shell *shell);
void			env_init(t_shell *shell, char **env);
void			run_unset(t_shell *shell);
int				run_export(t_exec_node *cmd, t_shell *shell);
t_env			*env_lstlast(t_env	*lst);

void			run_exit(t_shell *shell, char *str, char *s2);
void			add_environment(t_shell *shell, char *name, char *content);
int				run_cd(t_shell *shell, t_exec_node *cmd);
void			add_redirection_node(t_exec_node *exec, char *str, int type);
t_red			*create_redirection_node(char *str, int type);

void			print_redir_node(t_shell *shell);
void			ft_redirection(t_shell	*shell);
void			ft_error_msg(char *cmd, char *arg, char *msg);
int				ft_access(char *path);
void			set_io(t_exec_node *ex);
void			ft_dup_rev(t_exec_node *ex);

void			do_dollar(t_shell *shell, char *str, int *i);
void			quote_remove(t_shell *shell);
void			ft_init_signals(void);
int				control_howmany(char *str, char c);
int				err_msg(char *str);
int				istoken2(char *token);
void			tilda_control(t_shell *shell);

int				ft_check_syntax(char *str);
void			is_path_ok(char *path, char *cmd, int *ex_status);
void			is_dir(char *path);
char			*ft_getenv(t_env *envc, char *env_var);
void			ft_freeallnodes(t_shell *shell);
void			shell_readline(t_shell *shell);

int				trim_quote_plus(t_shell *shell, char *w, int i, char *tmp_str);
int				trim_quote_dllr(t_shell *shell, char *w, int i, char *tmp_str);

int				ft_perform_dup(int fd, int std_stream);

//export
t_env			*create_env(char *name, char *content);
int				check_and_update(t_shell *shell, char *name, char *content);
void			add_environment(t_shell *shell, char *name, char *content);
int				ft_is_all_num(char *str);
int				ft_isname(int c);
void			add_export(t_shell *shell, char *arg);
int				ft_check_syntax(char *str);

//init files
void			ft_freeallnodes(t_shell *shell);
char			**copyenv(char **env);
void			initalizer(t_shell *shell, char **env);
int				ft_is_all_space(char *str);
void			shell_readline(t_shell *shell);

//dnm.c funcs
void			ft_free_arr(char **str);
void			define_rtype(t_parse_node *node, t_exec_node *exnode);
t_exec_node		*get_exec_node(t_exec_node *exnode, int indx);
t_parse_node	*get_parse_node(t_parse_node *node, int indx);
void			put_cmnds(t_shell *shell);
int				ft_is_all_space(char *str);
int				ft_isspace(char c);
void			ft_heredoc(char *eof, int fd);
void			ft_redir_dless(t_exec_node *head, t_red *h_red, t_shell *shell);
void			ft_red_dgreat(t_exec_node *head, t_red *h_red, t_shell *shell);
void			ft_red_less(t_exec_node *ex, t_red *h_red, t_shell *shell);
void			ft_red_great(t_exec_node *head, t_red *h_red, t_shell *shell);
void			is_first_builtin(t_shell *shell, t_exec_node *ex);
void			ft_heredoc(char *eof, int fd);
void			free_redirections(t_shell *shell);
void			ft_free_intarr(int **num, t_shell *shell);
t_env			*copy_env_list(t_env *env_l);
void			handle_argument(char *arg, t_shell *shell);
void			sort_env_list(t_env *env_l);
void			print_exported_variable(t_env *env);
void			print_invalid_identifier_error(char *arg, t_shell *shell);
t_env			*env_copy(t_env *env);
void			env_sort(t_env **env);
t_env			*env_sorted_copy(t_env *env);
t_env			*env_listnew(char *name, char *content);
t_env			*env_lstlast(t_env *lst);
void			env_lstadd_back(t_env **lst, t_env *new);
void			node_control(t_shell *shell);
void			free_export_utils(t_env *tmp, t_env *tmp2);
char			*is_dir3(char *cmd, t_env *env);
void			spec_dol(t_shell *shell, char *str);
t_parse_node	*get_next_node(t_parse_node *current, t_parse_node **prev);
void			delete_null_nodes(t_shell *shell);
void			ft_parse(t_shell *shell);
void			ft_execpre(t_shell *shell);
void			cont_comnd(t_put_cmd	*local, t_shell *shell);
void			secondloop(t_put_cmd *local);
void			pipe_control(t_shell *shell);

#endif
