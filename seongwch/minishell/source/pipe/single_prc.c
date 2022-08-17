/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:54:05 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 16:09:59 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	single_total_cmd(t_process *storage, t_state *state, t_info *info)
{
	info->pid[0] = fork();
	if (info->pid[0] == -1)
	{
		ft_no_exit_error(PID_ERR);
		return ;
	}
	if (info->pid[0])
		waitpid(info->pid[0], NULL, WUNTRACED);
	else
		execute_cmd(storage->cmd, state);
}

static	void	single_built_cmd(t_process *storage, t_state *state, t_info *info)
{
	char	*str;

	if (redir_fd(info, storage->redir) == -1)
		return ;
	if (storage->cmd->start == NULL)
		return ;
	str = storage->cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(storage->cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		ft_env(state, storage->cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(storage->cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(storage->cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		ft_unset(storage->cmd, state);
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(storage->cmd);
	else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		ft_exit(storage->cmd, state);
	else
		single_total_cmd(storage, state, info);
}

void	single_process(t_process **storage, t_state *state)
{
	t_info	info;
	int		std_fd[2];
	char	*str;

	setting_herdoce(storage, &info);
	std_fd[0] = ft_dup(STDIN_FILENO);
	std_fd[1] = ft_dup(STDOUT_FILENO);
	init_info(storage, &info);
	info.prc_flag = 0;
	single_built_cmd(storage[0], state, &info);
	free(info.pid);
	ft_dup2(std_fd[0], STDIN_FILENO, info.prc_flag);
	ft_dup2(std_fd[1], STDOUT_FILENO, info.prc_flag);
}
