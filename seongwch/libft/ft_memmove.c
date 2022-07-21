/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:50:31 by seongwch          #+#    #+#             */
/*   Updated: 2021/12/11 18:11:39 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t			i;
	size_t			j;
	unsigned char	*dest_pt;
	unsigned char	*src_pt;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_pt = (unsigned char *)dest;
	src_pt = (unsigned char *)src;
	i = 0;
	j = 0;
	if (num == 0)
		return (dest);
	if (dest > src)
	{
		while (i < num)
			dest_pt[num - 1 - i++] = src_pt[num - 1 - j++];
	}
	else if (dest < src)
	{
		while (i < num)
			dest_pt[i++] = src_pt[j++];
	}
	return (dest);
}
