/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:54:16 by junoh             #+#    #+#             */
/*   Updated: 2022/06/18 20:16:02 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex_bonus.h"

void	ft_make_pipe(t_info *info, int index)
{
	int	pipe_ret;

	if (index % 2 == 0)
	{
		pipe_ret = pipe(info->pipe_alpha);
		if (pipe_ret < 0)
			ft_error(PIPE_ERR);
	}
	else
	{
		pipe_ret = pipe(info->pipe_beta);
		if (pipe_ret < 0)
			ft_error(PIPE_ERR);
	}
	return ;
}
