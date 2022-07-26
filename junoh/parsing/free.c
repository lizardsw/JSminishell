/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:30:23 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/26 18:50:20 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void 	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return ;
}

void	free_node(t_node *ptr)
{
	free(ptr->data);
	free(ptr);
}

void	free_list(t_list *list)
{
	t_node	*ptr;
	t_node	*temp;

	ptr = list->start;
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free_node(temp);
	}
	free(list);
}

void	free_process(t_process **prc)
{
	int	i;

	i = 0;
	while (prc[i] != NULL)
	{
		free_list(prc[i]->redir);
		free_list(prc[i]->cmd);
		free(prc[i]);
		i++;
	}
	free(prc);
}
