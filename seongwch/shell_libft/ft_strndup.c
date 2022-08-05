/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:00:11 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 14:00:23 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

char	*ft_strndup(const char *s, int cpy_len)
{
	char	*tmp;
	int		len;

	len = cpy_len;
	tmp = malloc(sizeof(char) * (cpy_len + 1));
	if (tmp == NULL)
		return (NULL);
	while (cpy_len-- > 0)
	{
		*tmp = *s;
		tmp++;
		s++;
	}
	*tmp = '\0';
	return (tmp - len);
}
