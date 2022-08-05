/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:59:11 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 13:59:45 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((n-- > 0) && !(!*s1 && !*s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
