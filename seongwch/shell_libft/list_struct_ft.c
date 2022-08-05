/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_struct_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:39:53 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 14:12:33 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

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
