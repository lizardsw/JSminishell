/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:50:56 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 20:13:03 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup(int fd)
{
	int	ret_value;

	ret_value = dup(fd);
	if (ret_value < 0)
		ft_no_exit_perror(DUP_ERR);
	return (ret_value);
}

int	ft_dup2(int fd1, int fd2, int flag)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	if (ret_value < 0 && flag == 1)
		ft_perror(DUP_ERR);
	else if (ret_value < 0 && flag == 0)
	{
		ft_no_exit_perror(DUP_ERR);
		return (ret_value);
	}
	close(fd1);
	return (ret_value);
}

void	ft_make_pipe(t_info *info)
{
	int	pipe_ret;

	pipe_ret = pipe(info->pipe_alpha);
	if (pipe_ret < 0 && info->prc_flag == 1)
		ft_error(PIPE_ERR);
	if (pipe_ret < 0 && info->prc_flag == 0)
		ft_no_exit_error(PIPE_ERR);
	return ;
}

int	cmd_compare(char *str1, char *str2)
{
	int	temp;

	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	temp = ft_strncmp(str1, str2, ft_strlen(str2));
	return (temp);
}
