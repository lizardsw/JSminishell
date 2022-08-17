/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:32:49 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 20:30:30 by seongwch         ###   ########.fr       */
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
	if (err == ARGS_NUM_ERR)
		ft_putstr_fd("Invalid number of arguments!", 2);
	else if (err == PID_ERR)
		ft_putstr_fd("Invalid pid", 2);
	else if (err == PIPE_ERR)
		ft_putstr_fd("Pipe failed", 2);
	exit(1);
}

void	ft_perror(int err)
{
	if (err == INFILE_OPEN_ERR)
	{
		perror("Infile open error!");
	}
	else if (err == OUTFILE_OPEN_ERR)
		perror("Outfile open error!");
	else if (err == EXE_ERR)
		perror("Execve error!");
	else if (err == PATH_ERR)
	{	
		perror("command not found");
		exit(127);
	}
	else if (err == DUP_ERR)
		perror("Dupplitcate error");
	exit(4);
}

int	ft_check_status(int temp)
{
	const int	w_status = temp & 0177; // WSTATUS(X) 0177 is octal number. it means 127 by decimal number
												// WSTATUS(X) = (status & 127)
	if (w_status == 0) // WIFEXITED(X) == (WSTATUS(X) == 0) -> if no signal end.
	{ 	printf("exit_code = %d\n", ((temp >> 8) & 0x000000ff));
		return ((temp >> 8) & 0x000000ff); // WEXITSTATUS(X) -> check exitcode and return its code
	}
	if (w_status != 0177 && w_status != 0) // WIFSIGNALED(X) -> if siganl end but not SIGSTOP and SIGCONT(these codes fill 3rd index with 127)
	{
		printf("status = %d\n", w_status);
		return (w_status); //WSTATUS(X) -> return its status code.
	}
	return (0);
}
