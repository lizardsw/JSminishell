/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_tmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:06:33 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 18:56:22 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static  void    remove_start(t_list *list, t_node *node)
{
    t_node  *node_next;

    node_next = list->start->next;
    list->start = node_next;
    node_next->prev = NULL;
    free(node->data);
    free(node);
    return ;
}

static  void    remove_last(t_list *list, t_node *node)
{
    t_node *node_prev;

    node_prev = list->end->prev;
    list->end = node_prev;
    node_prev->next = NULL;
    free(node->data);
    free(node);
    return ;
}

static  void    remove_middle(t_list *list, t_node *node)
{
    t_node *node_next;
    t_node *node_prev;

    node_next = node->next;
    node_prev = node->prev;
    node_prev->next = node_next;
    node_next->prev = node_prev;
    free(node->data);
    free(node);
    return ;
}

void    remove_node(t_list *list, t_node *node)
{
    t_node  *ptr;


    if (list->end == node)
    {
        remove_last(list, node);
        return ;
    }
    ptr = list->start;
    if (ptr == node)
    {
        remove_start(list, node);
        return ;
    }
    while (ptr != NULL)
    {
        if (ptr == node)
        {
            remove_middle(list, node);
            return ;
        }
        ptr = ptr->next;
    }
    printf("Can't search node\n");
}