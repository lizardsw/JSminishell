/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:06:04 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/21 21:51:03 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// syntax_node에 token을 라벨링 시켜줌
static void	label_token(t_node *ptr)
{
	char	*temp;

	temp = ptr->data;
	if (ptr->group == REDIR)
	{
		if (temp[0] == '<')
		{
			if (temp[1] == '<')
				ptr->token = RDRDIN;
			else
				ptr->token = RDIN;
		}
		else
		{
			if (temp[1] == '>')
				ptr->token = RDRDOUT;
			else
				ptr->token = RDOUT;
		}
	}
	else if (ptr->group == PIP)
		ptr->token = PIPE;
	else if (ptr->group == QUOTE || ptr->group == WORD)
		ptr->token = CMD;
}

// redir group node를 ast에 넣어줌.
static void	mv_redir_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	label_token(ptr);
	
	push_node_back(prc->redir, ptr);
	if (split->start != NULL && split->start->group != PIP \
			&& split->start->group != REDIR)
	{
		ptr = pop_node_front(split);
		label_token(ptr);
		push_node_back(prc->redir, ptr);
	}
}

//	cmd group node를 ast에 넣어줌.
static void	mv_cmd_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	label_token(ptr);
	push_node_back(prc->cmd, ptr);
}

// pip group node 확인 후, process toeken 바꿔주고 node free 해줌.
static void	mv_pip_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	if (ptr->data[0] == '|')
		prc->token = PIPE;
	free_node(ptr);
}

// ast 만드는 함수
t_process	**make_ast(t_list *list)
{
	t_process	**storage;
	t_node		*ptr;
	int			i;

	i = 0;
	ptr = list->start;
	storage = new_storage(list->pipe_num);
	while (ptr != NULL)
	{
		if (ptr->group == REDIR)
			mv_redir_syn(storage[i], list);
		else if (ptr->group == WORD | ptr->group == QUOTE)
			mv_cmd_syn(storage[i], list);
		else if (ptr->group == PIP)
		{
			mv_pip_syn(storage[i], list);
			i++;
		}
		ptr = list->start;
	}
	return (storage);
}
