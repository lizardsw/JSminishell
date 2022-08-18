/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_prc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:52:56 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 12:16:53 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	multi_total_cmd(t_list *cmd, t_state *state, t_info *info)
{
	char	*str;

	if (cmd->start == NULL)
		exit(1);
	str = cmd->start->data;
	if (cmd_compare(str, "cd") == 0)
		ft_cd(cmd, state);
	else if (cmd_compare(str, "env") == 0)
		ft_env(state, cmd->start);
	else if (cmd_compare(str, "export") == 0)
		ft_export(cmd, state);
	else if (cmd_compare(str, "pwd") == 0)
		ft_pwd(cmd, state);
	else if (cmd_compare(str, "unset") == 0)
		ft_unset(cmd, state);
	else if (cmd_compare(str, "echo") == 0)
		ft_echo(cmd);
	else if (cmd_compare(str, "exit") == 0)
		ft_exit(cmd, state, info->pid[info->number - 1]);
	else
		execute_cmd(cmd, state);
	exit(0);
}

static	void	child_prc(t_process *prc, t_state *state, t_info *info, int i)
{
	if (prc->index == START)
	{
		close(info->pipe_alpha[0]);
		ft_dup2(info->pipe_alpha[1], STDOUT_FILENO, info->prc_flag);
	}
	else if (prc->index == MIDDLE)
	{
		close(info->pipe_alpha[0]);
		ft_dup2(info->pre_pipe, STDIN_FILENO, info->prc_flag);
		ft_dup2(info->pipe_alpha[1], STDOUT_FILENO, info->prc_flag);
	}
	else
		ft_dup2(info->pre_pipe, STDIN_FILENO, info->prc_flag);
	redir_fd(info, prc->redir);
	multi_total_cmd(prc->cmd, state, info);
}

static	void	parent_prc(t_process *process, t_info *info, int i)
{
	if (process->index == START)
	{
		close(info->pipe_alpha[1]);
		info->pre_pipe = info->pipe_alpha[0];
	}
	else if (process->index == MIDDLE)
	{
		close(info->pipe_alpha[1]);
		if (info->pre_pipe != -1)
			close(info->pre_pipe);
		info->pre_pipe = info->pipe_alpha[0];
	}
	else
	{
		close(info->pipe_alpha[1]);
		if (info->pre_pipe != -1)
			close(info->pre_pipe);
	}
}

static	void	prc_while(t_process **storage, t_state *state, t_info *info)
{
	int	i;

	i = 0;
	while (storage[i] != NULL)
	{
		if (storage[i]->index != END)
			ft_make_pipe(info);
		info->pid[i] = fork();
		if (info->pid[i] < 0)
			ft_error(PID_ERR);
		if (info->pid[i])
			parent_prc(storage[i], info, i);
		else
			child_prc(storage[i], state, info, i);
		i++;
	}
}

void	multi_process(t_process **storage, t_state *state)
{
	int		i;
	t_info	info;
	int		temp;

	temp = 0;
	i = 0;
	init_info(storage, &info);
	info.prc_flag = 1;
	if (setting_herdoce(storage, &info) == -1)
	{
		free(info.pid);
		return ;
	}
	prc_while(storage, state, &info);
	while (i < info.number)
	{
		if (info.pid[info.number - 1] == wait(&temp))
			g_exit_status = ft_check_status(temp);
		i++;
	}
	free(info.pid);
}
