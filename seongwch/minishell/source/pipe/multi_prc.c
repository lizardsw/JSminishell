/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_prc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:52:56 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 14:56:06 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	void	multi_total_cmd(t_list *cmd, t_state *state)
{
	char	*str;

	if (cmd->start == NULL)
		exit(1);
	str = cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		ft_env(state, cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		ft_unset(cmd, state);
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		ft_exit(cmd, state);
	else
		execute_cmd(cmd, state);
	exit(1);
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
	multi_total_cmd(prc->cmd, state);
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
			parent_prc(storage[i], &info, i);
		else
			child_prc(storage[i], state, &info, i);
		i++;
	}
}

void	multi_process(t_process **storage, t_state *state)
{
	int		i;
	t_info	info;

	i = 0;
	init_info(storage, &info);
	info.prc_flag = 1;
	setting_herdoce(storage, &info);
	prc_while(storage, state, &info);
	while (i < info.number)
	{
		waitpid(info.pid[i], NULL, WUNTRACED);
		i++;
	}
	free(info.pid);
}
