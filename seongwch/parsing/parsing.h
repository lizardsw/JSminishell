#ifndef LIST_H
# define LIST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

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

typedef struct s_node
{
	struct s_node *prev;
	struct s_node *next;
	char	*data;
	int		group;
	int		token;
}	t_node;

typedef struct s_list
{
	t_node *start;
	t_node *end;
	int	number;
	int pipe_num;
	int state;
}	t_list;

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
	int		status
} t_state;

// list_struct.c
void	show_list(t_list *list);
t_list *new_list(void);
t_node *new_node(char *str);

// list_struct_ft.c
void	push_node_back(t_list *list, t_node *node);
void	push_node_front(t_list *list, t_node *node);
t_node *pop_node_back(t_list *list);
t_node *pop_node_front(t_list *list);

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

// error.c
int syntax_error(t_process **parsing);

// list_env.c
t_list	*make_list_env(char **env);
char	**split_key_value(char *str);
char	*get_value(t_list *env, char *key);

// shell_libft.c
char	*null_strjoin(char *s1, char *s2);
int		get_strchr(char *str, int number, char c);
char	*get_strdup(char *src, int number);

// expand_utils.c
int	cmd_expand(char **str_storage, char *str);
int	squote_expand(char **str_storage, char *str);
int	position_expand(char **str_storage, char *str, t_state *state, int is_dquote);
int	dquote_expand(char **str_storage, char *str, t_state *state);

// expand.c
void	expand_ast(t_process **ast, t_state *state);


#endif