/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strchr                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:50:40 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 13:50:58 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

// str에 number 만큼 c 를 찾아서 return 해준다.
int	get_strchr(char *str, int number, char c)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
