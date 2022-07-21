/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:52:19 by junoh             #+#    #+#             */
/*   Updated: 2022/06/20 18:31:11 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	ft_child_proc(t_info *info, int index)
{
	int	i;

	i = index;
	if (info->flag == 1)
	{
		if (i == 2)
			ft_dup2(info->fdin, STDIN_FILENO);
		close(info->pipe_alpha[0]);
		if (i != 2)
			ft_dup2(info->pipe_beta[0], STDIN_FILENO);
		ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);
		execute_cmd(info->argv[i], info->envp);
	}
	else
	{
		close(info->pipe_beta[0]);
		ft_dup2(info->pipe_alpha[0], STDIN_FILENO);
		ft_dup2(info->pipe_beta[1], STDOUT_FILENO);
		execute_cmd(info->argv[i], info->envp);
	}
	return ;
}
