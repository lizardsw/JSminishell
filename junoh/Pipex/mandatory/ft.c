/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:34:11 by junoh             #+#    #+#             */
/*   Updated: 2022/06/16 16:47:04 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

pid_t	ft_fork(void)
{
	pid_t	ret_pid;

	ret_pid = fork();
	if (ret_pid == -1)
		ft_error(PID_ERR);
	return (ret_pid);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	if (ret_value < 0)
		ft_perror(DUP_ERR);
	close(fd1);
	return (ret_value);
}

int	ft_check_stat(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
		return (WTERMSIG(stat));
	return (0);
}
