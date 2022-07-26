/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_struct_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:39:53 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/26 13:14:11 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	push_node_back(t_list *list, t_node *node)
{
	t_node	*ptr;

	list->number++;
	if (list->number == 1)
	{
		list->start = node;
		list->end = node;
		return ;
	}
	ptr = list->end;
	node->prev = ptr;
	ptr->next = node;
	list->end = node;
}

void	push_node_front(t_list *list, t_node *node)
{
	t_node	*ptr;

	list->number++;
	if (list->number == 1)
	{
		list->start = node;
		list->end = node;
		return ;
	}
	ptr = list->start;
	ptr->prev = node;
	node->next = ptr;
	list->start = node;
}

void	insert_node(t_list *list, t_node *front_node, t_node *node)
{
	t_node	*back_node;

	if (list->number == 0 || front_node->next == NULL)
	{
		push_node_back(list, node);
		return ;
	}
	list->number++;
	back_node = front_node->next;
	front_node->next = node;
	node->prev = front_node;
	node->next = back_node;
	back_node->prev = node;
}

t_node	*pop_node_back(t_list *list)
{
	t_node	*ptr;

	ptr = list->end;
	if (list->number == 0)
		return (NULL);
	list->number--;
	if (list->number == 0)
	{
		list->start = NULL;
		list->end = NULL;
		return (ptr);
	}
	list->end = ptr->prev;
	ptr->prev->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

t_node	*pop_node_front(t_list *list)
{
	t_node	*ptr;

	ptr = list->start;
	if (list->number == 0)
		return (NULL);
	list->number--;
	if (list->number == 0)
	{
		list->start = NULL;
		list->end = NULL;
		return (ptr);
	}
	list->start = ptr->next;
	ptr->next->prev = NULL;
	ptr->next = NULL;
	return (ptr);
}
