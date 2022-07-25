/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:41:07 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/25 18:53:59 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// syntax를 node화 시켜서 list로 push_back 해준다.
static int	push_syntax(t_list *list, char *str, int index, int len)
{
	t_node	*new;
	char	*temp;

	temp = get_strdup(&str[index], len);
	new = new_node(temp);
	new->group = check_group(str[0]);
	push_node_back(list, new);
	free(temp);
	return (len);
}

static int	label_group_util(t_list *split_list, char *str)
{
	int	add_index;
	int	i;

	add_index = 0;
	i = 0;
	if (check_group(str[0]) == QUOTE)
	{
		i = 1;
		while (str[0] != str[i] && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			split_list->state = ERROR;
		add_index = push_syntax(split_list, str, 1, i - 1) + 2;
	}
	else if (check_group(str[0]) == SPACES)
	{
		while (str[i] == ' ')
			i++;
		add_index = i;
	}
	return (add_index);
}

// syntax를 group에 따라 다르게 처리해준다.
static int	label_group(t_list *split_list, char *str)
{
	int		add_index;

	add_index = 0;
	if (check_group(str[0]) == PIP)
	{
		add_index = push_syntax(split_list, str, 0, 1);
		split_list->pipe_num++;
	}
	else if (check_group(str[0]) == REDIR)
	{
		if (str[0] == str[1])
			add_index = push_syntax(split_list, str, 0, 2);
		else
			add_index = push_syntax(split_list, str, 0, 1);
	}
	else
		add_index = label_group_util(split_list, str);
	return (add_index);
}

// 문자열을 syntax단위로 나누어서 list로 만들어준다.
t_list	*shell_split(char *str)
{
	t_list	*split_list;
	int		check;
	int		i;
	int		j;

	i = 0;
	split_list = new_list();
	if (str[0] == '\0')
		split_list->state = BLANK;
	while (str[i] != '\0')
	{
		j = 0;
		while (check_group(str[i + j]) == WORD || check_group(str[i + j]) == QUOTE)
			j++;
		if (j != 0)
			push_syntax(split_list, &str[i], 0, j);
		check = label_group(split_list, &str[i + j]);
		j += check;
		i = i + j;
		if (i > ft_strlen(str))
			break ;
	}
	return (split_list);
}
