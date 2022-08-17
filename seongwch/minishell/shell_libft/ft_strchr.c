/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:53:46 by junoh             #+#    #+#             */
/*   Updated: 2022/08/17 19:18:03 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)&str[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
