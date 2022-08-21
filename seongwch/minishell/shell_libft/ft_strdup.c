/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:05:27 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/21 15:17:37 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

// ft_strdup 24~28 add;
char	*ft_strdup(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	if (str == NULL)
	{
		new[i] = '\0';
		return (new);
	}
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
