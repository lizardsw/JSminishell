/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:35:37 by junoh             #+#    #+#             */
/*   Updated: 2022/08/21 15:16:01 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
	return ;
}

static	void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
	return ;
}

static	int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static	void	print_echo(t_list *cmd_list, int flag)
{
	t_node	*ptr;
	int		arg;

	arg = 0;
	ptr = cmd_list->start->next;
	if (flag == 1)
	{
		if (ptr->next == NULL)
			return ;
		ptr = ptr->next;
	}
	while (ptr != NULL)
	{		
		if (!check_flag(ptr->data) || arg)
		{
			arg = 1;
			ft_putstr(ptr->data);
		}
		if ((!check_flag(ptr->data) && ptr->next != NULL) || \
		(arg == 1 && check_flag(ptr->data)))
			ft_putchar(' ');
		ptr = ptr->next;
	}
	return ;
}

void	ft_echo(t_list *cmd_list)
{
	t_node	*ptr;
	int		flag;

	ptr = cmd_list->start;
	flag = 0;
	if (ptr->next == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (check_flag(cmd_list->start->next->data) == 1)
		flag = 1;
	print_echo(cmd_list, flag);
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return ;
}
