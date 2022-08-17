/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_libft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:46:51 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 19:18:26 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_LIBFT_H
# define SHELL_LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	char			*data;
	int				group;
	int				token;
}	t_node;

typedef struct s_list
{
	t_node	*start;
	t_node	*end;
	int		number;
	int		pipe_num;
	int		state;
}	t_list;

//	str 관련된
char	*null_strjoin(char *s1, char *s2);
int		get_strchr(char *str, int number, char c);
char	*get_strdup(char *src, int number);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		ft_strichr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_path_join(char *s1, char *s2);
char	*ft_strndup(const char *s, int cpy_len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
int		ft_isalpha(int c);
char	*ft_itoa(int n);

// list 관련된
void	show_list(t_list *list);
t_list	*new_list(void);
t_node	*new_node(char *str);
void	push_node_back(t_list *list, t_node *node);
void	push_node_front(t_list *list, t_node *node);
t_node	*pop_node_back(t_list *list);
t_node	*pop_node_front(t_list *list);
void	remove_node(t_list *list, t_node *node);

#endif