/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:42:23 by seongwch          #+#    #+#             */
/*   Updated: 2021/12/08 19:47:27 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;
	char	*dest_pt;
	char	*src_pt;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	dest_pt = (char *)dest;
	src_pt = (char *)src;
	while (i < num)
	{
		dest_pt[i] = src_pt[i];
		i++;
	}
	return (dest);
}
