/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:30:23 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 14:36:47 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_str(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return ;
}

void	free_node(t_node *ptr)
{
	if (ptr == NULL)
		return ;
	free(ptr->data);
	free(ptr);
}

void	free_list(t_list *list)
{
	t_node	*ptr;
	t_node	*temp;

	if (list == NULL)
		return ;
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
	if (prc == NULL)
		return ;
	while (prc[i] != NULL)
	{
		free_list(prc[i]->redir);
		free_list(prc[i]->cmd);
		free(prc[i]);
		i++;
	}
	free(prc);
}

void	path_frees(char **strs, char *str)
{
	int	i;

	i = 0;
	if (strs != NULL)
	{
		while (strs[i] != NULL)
			free(strs[i++]);
		free(strs[i]);
		free(strs);
	}
	else
		free(str);
}
