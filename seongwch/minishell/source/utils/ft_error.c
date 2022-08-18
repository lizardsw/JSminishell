/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:32:49 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 16:52:43 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		ft_putchar_fd(*str++, fd);
	return ;
}

void	ft_error(int err)
{
	if (err == PID_ERR)
		ft_putstr_fd("Invalid pid\n", 2);
	else if (err == PIPE_ERR)
		ft_putstr_fd("Pipe failed\n", 2);
	exit(1);
}

void	ft_perror(int err)
{
	if (err == INFILE_OPEN_ERR)
	{
		ft_str_error("Infile open error!");
		exit(1);
	}
	else if (err == OUTFILE_OPEN_ERR)
	{
		ft_str_error("Outfile open error!");
		exit(1);
	}
	else if (err == EXE_ERR)
		ft_str_error("Execve error!");
	else if (err == PATH_ERR)
		ft_str_error("command not found");
	else if (err == DUP_ERR)
	{
		ft_str_error("Dupplitcate error");
		exit(1);
	}
	exit(127);
}

int	ft_check_status(int temp)
{
	const int	w_status = temp & 0177;

	if (w_status == 0)
	{
		return ((temp >> 8) & 0x000000ff);
	}
	if (w_status != 0177 && w_status != 0)
	{
		return (w_status);
	}
	return (0);
}
