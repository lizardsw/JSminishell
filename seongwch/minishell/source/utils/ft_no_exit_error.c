/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_exit_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:59:44 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 15:02:19 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_str_error(char *str1)
{
	char	*temp;

	temp = strerror(errno);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(temp, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_no_exit_error(int err)
{
	if (err == PID_ERR)
		ft_putstr_fd("Invalid pid\n", 2);
	else if (err == PIPE_ERR)
		ft_putstr_fd("Pipe failed\n", 2);
	else if (err == SYN_ERR)
		ft_putstr_fd("syntax failed\n", 2);
	else if (err == QUOTE_ERR)
		ft_putstr_fd("Quote failed\n", 2);
	g_exit_status = 1;
}

void	ft_no_exit_perror(int err)
{
	if (err == INFILE_OPEN_ERR)
		ft_str_error("Infile open error!");
	else if (err == OUTFILE_OPEN_ERR)
		ft_str_error("Outfile open error!");
	else if (err == EXE_ERR)
		ft_str_error("Execve error!");
	else if (err == PATH_ERR)
		ft_str_error("command not found");
	else if (err == DUP_ERR)
	{
		ft_str_error("Dupplitcate error");
		g_exit_status = 1;
		return ;
	}
	g_exit_status = 127;
}
