/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:18:22 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 19:19:29 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

enum list_state
{
	ERROR = -1,
	BLANK = 0,
	GOOD = 1
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
	int		status;
} t_state;

// list_env.c
t_list	*make_list_env(char **env);
char	**split_key_value(char *str);
char	**make_char_env(t_list *list);
char	*get_value(t_list *env, char *key);

// list_struct_ft.c
void	push_node_back(t_list *list, t_node *node);
void	push_node_front(t_list *list, t_node *node);
t_node *pop_node_back(t_list *list);
t_node *pop_node_front(t_list *list);

// list_struct.c
void	show_list(t_list *list);
t_list *new_list(void);
t_node *new_node(char *str);

// ft_env.c
int ft_env(t_state *state, t_node *cmd_node);

// ft_export.c
t_node     *is_key_exist_without_value(t_state *state, char *key, int flag);
void    exec_export(t_node *cmd_node, t_state *state);
void    ft_export(t_list *cmd_list, t_state *state);

// ft_export_print.c
void    export_print(t_state *state);
void    export_print_with_value(t_state *state, t_node *node);

// shell_libft.c
char	*null_strjoin(char *s1, char *s2);
int		get_strchr(char *str, int number, char c);
char	*get_strdup(char *src, int number);

// free.c
void 	free_str(char **str);
void	free_node(t_node *ptr);
void	free_list(t_list *list);
void	free_process(t_process **prc);

// ft_unset.c
int     check_str(char *str);
void    del_env_one(t_node *cmd_node, t_state *state, t_node *ptr);
void    exec_unset(t_node *cmd_node, t_state *state);
void    ft_unset(t_list *cmd_list, t_state *state);

// list_remove_tmp.c
void	remove_node(t_list *list, t_node *node);

// ft_cd.c
void    ft_cd(t_list *cmd_list, t_state *state);
void    change_dir(char *path, t_state *state);
void    change_env_path(t_state *state, char *key, int flag);

//ft_pwd.c
int ft_pwd(t_list *cmd_list, t_state *state);
# endif
// first try -> gcc -g3 -fsanitize=address libft.a ft_cd.c ft_pwd.c ft_unset.c list_remove_tmp.c list_env.c list_struct.c list_struct_ft.c ft_env.c ft_export.c ft_export_print.c main.c shell_libft.c free.c