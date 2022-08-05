#include "parsing.h"

int	ft_dup2(int fd1, int fd2)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	if (ret_value < 0)
		ft_perror(DUP_ERR);
	close(fd1);
	return (ret_value);
}

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

void child_process(t_process *process, t_state *state, t_info *info, int i)
{
	// printf("child i : %d\n", i);
	if (i % 2 == 0)
	{
		close(info->pipe_alpha[0]);
		if (i != 0)
			ft_dup2(info->pipe_beta[0], STDIN_FILENO);
		if (i < info->number - 1)
			ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);
	}
	else
	{
		close(info->pipe_beta[0]);
		ft_dup2(info->pipe_alpha[0], STDIN_FILENO);
		if (i < info->number - 1)
			ft_dup2(info->pipe_beta[1], STDOUT_FILENO);
	}
	// write(2, "child!\n", 7);
	redir_fd(info, process->redir);
	multi_total_cmd(process->cmd, state);
}

void parent_process(t_info *info, int i)
{
	// printf("parent i : %d\n", i);
	if (i % 2 == 0)
	{
		close(info->pipe_alpha[1]);
		if (i != 0 && i < info->number - 1)
			close(info->pipe_beta[0]);
	}
	else
	{
		close(info->pipe_beta[1]);
		if (i < info->number - 1)
			close(info->pipe_alpha[0]);
	}
}

void	init_info(t_process **storage, t_info *info)
{
	t_process	*ptr;
	int			i;

	i = 0;
	while (storage[i] != NULL)
		i++;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (info->pid == NULL)
		exit(1);
	info->number = i;
	info->pre_pipe = -1;
	info->fd_in = -2;
	info->fd_out = -2;
}

void multi_process(t_process **storage, t_state *state)
{
	int	i;
	t_info info;

	i = 0;
	init_info(storage, &info);
	while (storage[i] != NULL)
	{
		// printf("i : %d, info.number : %d\n", i, info.number);
		if (i != info.number)
		{
			// printf("create pipe\n");
			ft_make_pipe(&info, i);
		}
		info.pid[i] = fork();
		if (info.pid[i])
			parent_process(&info, i);
		else
			child_process(storage[i], state, &info, i);
		i++;
	}
	i = 0;
	while(i < info.number)
	{
		wait(NULL);
		i++;
	}
	free(info.pid);
}

void single_process(t_process **storage, t_state *state)
{
	char *str;

	str = storage[0]->cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(storage[0]->cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(state, storage[0]->cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(storage[0]->cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(storage[0]->cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(storage[0]->cmd, state);
	else
		multi_process(storage, state);
}

void pipe_main(t_process **storage, t_state *state)
{
	if (storage[0]->token == PIPE)
	{
		multi_process(storage, state);
	}
	else
	{
		single_process(storage, state);
		// execute_cmd(storage[0]->cmd, state);
	}
}