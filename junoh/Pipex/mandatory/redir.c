/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:55:12 by junoh             #+#    #+#             */
/*   Updated: 2022/06/20 19:21:07 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static	void	ft_pipe_to_outfile(t_info *info, int index)
{
	if (index % 2 == 1)
		ft_dup2(info->pipe_alpha[0], STDIN_FILENO);
	else
		ft_dup2(info->pipe_beta[0], STDIN_FILENO);
	return ;
}

static int	ft_last_cmd(t_info *info)
{
	int	i;
	int	ret;

	ret = 0;
	i = info->argc;
	info->fdout = open_file(info->argv[info->argc - 1], STDOUT_FILENO);
	info->pid[info->argc - 4] = ft_fork();
	if (info->pid[info->argc - 4] == 0)
	{
		ft_pipe_to_outfile(info, i);
		ft_dup2(info->fdout, STDOUT_FILENO);
		execute_cmd(info->argv[info->argc - 2], info->envp);
	}
	if (info -> argc == 5)
		close(info->pipe_alpha[0]);
	while (i-- > 3)
	{
		if (info->pid[info->argc - 4] == wait(&info->status))
			ret = ft_check_status(info);
	}	
	return (ret);
}

int	ft_redir(t_info *info)
{
	int	i;

	i = 2;
	info->flag = 1;
	while (i < info->argc - 2)
	{
		ft_make_pipe(info, i);
		info->pid[i - 2] = ft_fork();
		if (info->pid[i - 2])
			ft_parent_proc(info, i);
		else
			ft_child_proc(info, i);
		info->flag *= -1;
		i++;
	}
	return (ft_last_cmd(info));
}
