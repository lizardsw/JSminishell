/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:23:39 by junoh             #+#    #+#             */
/*   Updated: 2022/08/18 12:24:27 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"shell_libft.h"
#include <limits.h> 

static	long	ft_strtol(const char *str)
{
	long	sign;
	long	tmp;
	long	sum;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	sum = 0;
	tmp = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = (sum * 10) + sign * (*str - '0');
		if (sum > 0 && tmp < 0)
			return (LONG_MAX);
		if (sum < 0 && tmp > 0)
			return (LONG_MIN);
		sum = tmp;
		str++;
	}
	return (sum);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str));
}