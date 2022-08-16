#ifndef LIST_H
# define LIST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../shell_libft/shell_libft.h"

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

#include <fcntl.h>
#include <string.h>
#include <errno.h>

enum group
{
	WORD = 0,
	SPACES = 1,
	REDIR = 2,
	PIP = 3,
	QUOTE = 4,
	ZERO = 5
};

enum token
{
	CMD = 0,
	RDIN = 1,
	RDOUT = 2,
	RDRDIN = 3,
	RDRDOUT = 4,
	PIPE = 5
};

enum list_state
{
	ERROR = -1,
	BLANK = 0,
	GOOD = 1
};

enum prcindex
{
	START = 0,
	MIDDLE = 1,
	END = 2
};

enum e_error
{
	ARGS_NUM_ERR,
	PID_ERR,
	INFILE_OPEN_ERR,
	OUTFILE_OPEN_ERR,
	PATH_ERR,
	EXE_ERR,
	PIPE_ERR,
	DUP_ERR
};

typedef struct s_process
{
	t_list	*redir;
	t_list	*cmd;
	int		token;
	int		index;
} t_process;

typedef struct s_state
{
	t_list *env_lst;
	char	*old_pwd;
	char	*pwd;
	int		status;
} t_state;

typedef struct s_info
{
	int	fd_in;
	int	fd_out;
	int	number;
	int	prc_flag;
	int pre_pipe;
	int	pipe_alpha[2];
	int	pipe_beta[2];
	pid_t	*pid;
}	t_info;

int	g_exit_status;

// shell_split.c
t_list *shell_split(char *str);

// shell_split_utils.c
int	check_group(char c);
void	label_token(t_node *ptr);
int	dq_strlen(t_list *list, char *str);

// make_ast.c
t_process **make_ast(t_list *list);

// make_ast_utils.c
void	show_process(t_process **ptr);
t_process *new_process(void);
t_process **new_storage(int pipe_num);

// free.c
void 	free_str(char **str);
void	free_node(t_node *ptr);
void	free_list(t_list *list);
void	free_process(t_process **prc);
void	path_frees(char **strs, char *str);

// error.c
int syntax_error(t_process **parsing);

// list_env.c
t_list	*make_list_env(char **env);
char	**split_key_value(char *str);
char	**make_char_env(t_list *list);
char	*get_value(t_list *env, char *key);

// expand_utils.c
int	cmd_expand(char **str_storage, char *str);
int	squote_expand(char **str_storage, char *str);
int	position_expand(char **str_storage, char *str, t_state *state, int is_dquote);
int	dquote_expand(char **str_storage, char *str, t_state *state);

// expand.c
void	expand_ast(t_process **ast, t_state *state);

// signal.c
void signal_handler();
void setting_terminal();
void here_signal_handler();

// setting_fd.c
int		redir_fd(t_info *info, t_list *redir);

// pipe_main.c
int		ft_dup2(int fd1, int fd2, int flag);
void	ft_make_pipe(t_info *info);
void child_process(t_process *process, t_state *state, t_info *info, int i);
void parent_process(t_process *process, t_info *info, int i);
void	init_info(t_process **storage, t_info *info);
void multi_process(t_process **storage, t_state *state);
void pipe_main(t_process **storage, t_state *state);

// execute_cmd.c
void	execute_cmd(t_list *redir, t_state *state);

// ft_perror.c
void	ft_perror(int err);
void	ft_error(int err);
void	ft_no_exit_perror(int err);
void	ft_no_exit_error(int err);

// builtin_package.c
void	multi_total_cmd(t_list *cmd, t_state *state);
void	single_built_cmd(t_process *storage, t_state *state, t_info *info);

// here_doc
void    setting_herdoce(t_process **storage, t_info *info);

// built-in
void    change_env_path(t_state *state, char *key, int flag);
void    change_dir(char *path, t_state *state);
void    ft_cd(t_list *cmd_list, t_state *state);
int ft_env(t_state *state, t_node *cmd_node);

void    export_print_with_value(t_state *state, t_node *node);
void    export_print(t_state *state);
void    ft_export(t_list *cmd_list, t_state *state);
int 	compare_str(char *s1, char *s2);
void    classify_export(char **args, char **origin, t_node *arg_node, \
int flag, t_list *env);
void     check_key(t_node *node, t_list *env_lst);
void    replace_node(t_node *new_node, t_list *env_lst);

void	ft_echo(t_list *cmd_list);

void	ft_exit(t_list *cmd_list ,t_state *state);

int ft_pwd(t_list *cmd_list, t_state *state);
int     check_str(char *str);
void    del_env_one(t_node *cmd_node, t_state *state, t_node *ptr);
void    exec_unset(t_node *cmd_node, t_state *state);
void    ft_unset(t_list *cmd_list, t_state *state);

#endif