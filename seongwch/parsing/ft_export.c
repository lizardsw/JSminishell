/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:10:39 by junoh             #+#    #+#             */
/*   Updated: 2022/08/08 16:12:48 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node     *is_key_exist_without_value(t_state *state, char *key, int flag)
{
	t_node  *lst;
	char    *cmp_buf;
	char    **split;
	
	lst = state->env_lst->start;
	cmp_buf = get_strdup(key, (int)ft_strlen(key) - flag);
	while (lst->next != NULL)
	{
		split = split_key_value(lst->data);
		if ((!ft_strncmp(cmp_buf, split[0], ft_strlen(key) - flag) && \
		((int)ft_strlen(split[0]) == (int)ft_strlen(key) - flag)))
		{
			free_str(split);
			return (new_node(ft_strdup(lst->data)));
		}
		lst = lst->next;
	}        
	free_str(split);
	return (NULL);
}

static  void    change_and_add_env_lst(t_state *state, char **split, t_node *cmd_node)
{
	t_node *node;
	   
	node = is_key_exist_without_value(state, split[0], 1); // 환경변수 a=3 이나 a=가 아닌 a 일떼
	if (node)
	{
		node->data = ft_strjoin(node->data, "=");
		node->data = ft_strjoin(node->data, split[1]);
	}
	else
	{
		node = is_key_exist_without_value(state, split[0], 0); //  a 조차 없다면 a= 을 만듬
		if (node)
			node->data = ft_strjoin(node->data, split[1]);
		else
			push_node_back(state->env_lst, new_node(cmd_node->data));
	}
	free_str(split);
	return ;
}

static  void    exchange_env_lst(t_node *node, t_state *state)
{
	char    **morpheme; 
	t_node  *n_node;
		
	morpheme = split_key_value(node->data);
	n_node = NULL;
	morpheme[0] = ft_strjoin(morpheme[0], "="); // ft_strjoin 수정함
	if (morpheme[1] == NULL) // export a=
	{ 
		n_node = is_key_exist_without_value(state, morpheme[0], 1);
		if (n_node)
			n_node->data = ft_strjoin(n_node->data, "=");
		else
			push_node_back(state->env_lst, new_node(morpheme[0]));
		free_str(morpheme);
	}
	else
		change_and_add_env_lst(state, morpheme, node);
}

void    exec_export(t_node *cmd_node, t_state *state)
{
	t_node *ptr;
	
	ptr = cmd_node;
	if (ptr->next == NULL)
	{
		export_print(state);
		return ;
	}
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (ft_strlen(ptr->data) == 1 && ptr->data[0] == '_')
			;
		else if (!ft_strchr(ptr->data, '='))
			change_env_lst(ptr, state);
		else
			push_node_back(state->env_lst, new_node(ptr->data));
		ptr = ptr->next;
	}
	return ;
}

void    ft_export(t_list *cmd_list, t_state *state)
{
	exec_export(cmd_list->start, state);
	return ;
}