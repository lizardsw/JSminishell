/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_exit_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:59:44 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 14:31:00 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_no_exit_error(int err)
{
	if (err == ARGS_NUM_ERR)
		ft_putstr_fd("Invalid number of arguments!", 2);
	else if (err == PID_ERR)
		ft_putstr_fd("Invalid pid", 2);
	else if (err == PIPE_ERR)
		ft_putstr_fd("Pipe failed", 2);
}

void	ft_no_exit_perror(int err)
{
	if (err == INFILE_OPEN_ERR)
		perror("Infile open error!");
	else if (err == OUTFILE_OPEN_ERR)
		perror("Outfile open error!");
	else if (err == EXE_ERR)
		perror("Execve error!");
	else if (err == PATH_ERR)
		perror("command not found");
	else if (err == DUP_ERR)
		perror("Dupplitcate error");
}
