/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:12 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/09 09:26:13 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

void	show_list(t_list *list)
{
	t_node	*ptr;

	ptr = list->start;
	if (ptr == NULL)
		printf("EMPTY! list");
	while (ptr != NULL)
	{
		printf("[%s gt(%d,%d)]", ptr->data, ptr->group, ptr->token);
		ptr = ptr->next;
	}
	printf("\n");
}

t_list	*new_list(void)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		exit(1);
	new->start = NULL;
	new->end = NULL;
	new->number = 0;
	new->pipe_num = 0;
	new->state = 1;
	return (new);
}

t_node	*new_node(char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		exit(1);
	new->next = NULL;
	new->prev = NULL;
	new->data = ft_strdup(str);
	new->token = -1;
	new->group = -1;
	return (new);
}
