/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:02:12 by seongwch          #+#    #+#             */
/*   Updated: 2021/11/27 19:30:40 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	make_size(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	fill_char(char *str, int n, size_t size)
{
	size_t	i;
	int		temp;

	i = size - 1;
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		temp = n % 10;
		if (temp < 0)
			temp = -temp;
		str[i] = temp + '0';
		n = n / 10;
		i--;
	}
	str[size] = '\0';
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*new;

	size = make_size(n);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	fill_char(new, n, size);
	return (new);
}
