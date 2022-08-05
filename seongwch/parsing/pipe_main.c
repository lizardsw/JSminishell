#include "parsing.h"

int	ft_dup2(int fd1, int fd2)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	// error
	close(fd1);
	return (ret_value);
}

void	ft_make_pipe(t_info *info, int index)
{
	int	pipe_ret;

	if (index % 2 == 0)
	{
		pipe_ret = pipe(info->pipe_alpha);
		// error
	}
	else
	{
		pipe_ret = pipe(info->pipe_beta);
		// error
	}
	return ;
}

void child_process(t_process *process, t_state *state, t_info *info, int i)
{
	if (i % 2 == 0)
	{
		close(info->pipe_alpha[0]);
		if (i != 0)
			ft_dup2(info->pipe_beta[0], STDIN_FILENO);
		if (i != info->number)
			ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);
	}
	else
	{
		close(info->pipe_beta[0]);
		ft_dup2(info->pipe_alpha[0], STDIN_FILENO);
		if (i != info->number)
			ft_dup2(info->pipe_beta[1], STDOUT_FILENO);
	}
	redir_fd(info, process->redir);
	execute_cmd(process->redir, state->env_lst);
}

void parent_process(t_info *info, int i)
{
	if (i == 0)
	{
		close(info->pipe_alpha[1]);
		if (i != 0 || i != info->number)
			close(info->pipe_beta[0]);
	}
	else
	{
		close(info->pipe_beta[1]);
		if (i != info->number)
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
	info->fd_in = 0;
	info->fd_out = 0;
}

void multi_process(t_process **storage, t_state *state)
{
	int	i;
	t_info info;

	i = 0;
	init_info(storage, &info);
	while (storage[i] != NULL)
	{
		if (i != info.number)
			ft_make_pipe(&info, i);
		info.pid[i] = fork();
		if (info.pid[i] == 0)
			child_process(storage[i], state, &info, i);
		else
			parent_process(&info, i);
		i++;
	}
	while()
	{
		// wait
	}
}

void pipe_main(t_process **storage, t_state *state)
{
	int i;

	i = 0;
	if (storage[0]->token == PIPE)
	{

	}
	else
	{

	}
}