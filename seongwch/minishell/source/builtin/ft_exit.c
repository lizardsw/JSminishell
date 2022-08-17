/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:52:46 by junoh             #+#    #+#             */
/*   Updated: 2022/08/17 16:05:28 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h> //  넣어도 되는 것일까?

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

static	int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str));
}

static	int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static	void	exit_not_num(char *str)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", str);
	exit(255);
}

void	ft_exit(t_list *cmd_list ,t_state *state)
{
	int	ret;

	if (cmd_list->number == 1)
	{
		printf("exit\n");
		exit(state->status);
	}
	else if (cmd_list->number == 2)
	{
		if (is_num_str(cmd_list->start->next->data))
		{
			ret = ft_atoi(cmd_list->start->next->data);
			printf("exit\n");
			exit(ret);
		}
		else
			exit_not_num(cmd_list->start->next->data);
	}
	else
	{
		printf("bash: exit: too many arguments\n");
		state->status = 1;
	}
}
