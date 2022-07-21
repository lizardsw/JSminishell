/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:34:14 by seongwch          #+#    #+#             */
/*   Updated: 2021/12/01 18:27:32 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	t_list	*ptr;

	ptr = lst;
	if (lst == NULL)
		return (NULL);
	newlst = NULL;
	while (ptr != NULL)
	{
		newnode = ft_lstnew(f(ptr -> content));
		if (newnode == NULL)
		{
			ft_lstclear(&newlst, del);
			return (newlst);
		}
		ft_lstadd_back(&newlst, newnode);
		ptr = ptr -> next;
	}
	return (newlst);
}
