/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:52:46 by junoh             #+#    #+#             */
/*   Updated: 2022/08/18 15:06:59 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (1);
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

static	void	exit_less_arg(t_node *node, int number, pid_t pid)
{
	int	temp;

	temp = 0;
	if (number == 1)
	{
		if (pid != 0)
			printf("exit\n");
		g_exit_status = 0;
		exit(g_exit_status);
	}
	else if (number == 2)
	{
		temp = ft_atoi(node->next->data);
		g_exit_status = temp;
		if ((temp < 10 && temp > -10) && ft_strlen(node->next->data) > 17)
		{
			printf("bash: exit: %s: numeric argument required\n", \
					node->next->data);
			g_exit_status = 255;
		}
		if (pid != 0)
			printf("exit\n");
		exit(g_exit_status);
	}
}

void	ft_exit(t_list *cmd_list, t_state *state, pid_t pid)
{
	if (cmd_list->number != 1 && !is_num_str(cmd_list->start->next->data))
	{
		printf("debug2\n");
		exit_not_num(cmd_list->start->next->data);
		printf("debug3\n");
	}
	else
	{
		if (cmd_list->number <= 2)
		{
			exit_less_arg(cmd_list->start, cmd_list->number, pid);
		}
		else
		{
			printf("bash: exit: too many arguments\n");
			g_exit_status = 1;
		}
	}
}
