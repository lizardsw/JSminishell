/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:28:17 by seongwch          #+#    #+#             */
/*   Updated: 2021/11/22 17:57:11 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	char_c;
	size_t			i;

	i = 0;
	char_c = (unsigned char)c;
	ptr = (unsigned char *)str;
	while (i < n)
	{
		if (ptr[i] == char_c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
