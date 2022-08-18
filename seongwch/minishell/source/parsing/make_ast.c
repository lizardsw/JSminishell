/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:06:04 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 15:26:39 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	mv_cmd_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	label_token(ptr);
	push_node_back(prc->cmd, ptr);
}

static void	mv_pip_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	if (ptr->data[0] == '|')
		prc->token = PIPE;
	free_node(ptr);
}

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
