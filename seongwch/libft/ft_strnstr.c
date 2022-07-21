/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:51:58 by seongwch          #+#    #+#             */
/*   Updated: 2021/12/05 21:14:01 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (src[0] == '\0')
		return ((char *)&dest[0]);
	while (i < len && dest[i] != '\0')
	{
		j = 0;
		if (dest[i] == src[j])
		{
			while (dest[i + j] == src[j] && i + j < len)
			{
				j++;
				if (src[j] == '\0')
					return ((char *)&dest[i]);
			}
		}
		i++;
	}
	return (NULL);
}
