/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:54:05 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 20:16:09 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	single_cmd(t_process *storage, t_state *state, t_info *info)
{
	int	temp;

	temp = 0;
	info->pid[0] = fork();
	if (info->pid[0] == -1)
	{
		ft_no_exit_error(PID_ERR);
		return ;
	}
	if (!info->pid[0])
		execute_cmd(storage->cmd, state);
	if (info->pid[0] == wait(&temp))
		g_exit_status = ft_check_status(temp);
}

static	void	single_built(t_process *storage, t_state *state, t_info *info)
{
	char	*str;

	if (redir_fd(info, storage->redir) == -1)
		return ;
	if (storage->cmd->start == NULL)
		return ;
	str = storage->cmd->start->data;
	if (cmd_compare(str, "cd") == 0)
		ft_cd(storage->cmd, state);
	else if (cmd_compare(str, "env") == 0)
		ft_env(state, storage->cmd->start);
	else if (cmd_compare(str, "export") == 0)
		ft_export(storage->cmd, state);
	else if (cmd_compare(str, "pwd") == 0)
		ft_pwd(storage->cmd, state);
	else if (cmd_compare(str, "unset") == 0)
		ft_unset(storage->cmd, state);
	else if (cmd_compare(str, "echo") == 0)
		ft_echo(storage->cmd);
	else if (cmd_compare(str, "exit") == 0)
		ft_exit(storage->cmd, state);
	else
		single_cmd(storage, state, info);
}

void	single_process(t_process **storage, t_state *state)
{
	t_info	info;
	int		std_fd[2];
	char	*str;

	init_info(storage, &info);
	info.prc_flag = 0;
	if (setting_herdoce(storage, &info) == -1)
	{
		free(info.pid);
		return ;
	}
	std_fd[0] = ft_dup(STDIN_FILENO);
	std_fd[1] = ft_dup(STDOUT_FILENO);
	single_built(storage[0], state, &info);
	free(info.pid);
	ft_dup2(std_fd[0], STDIN_FILENO, info.prc_flag);
	ft_dup2(std_fd[1], STDOUT_FILENO, info.prc_flag);
}
