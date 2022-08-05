/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strdup                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:51:10 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 13:51:34 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

// str에 number만큼 strdup
char	*get_strdup(char *src, int number)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * number + 1);
	if (new == NULL)
		exit(1);
	while (i < number)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
