#include "parsing.h"

int	ft_dup2(int fd1, int fd2)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	// printf("fd1 : %d , fd2 : %d, ret_value : %d\n", fd1, fd2, ret_value);
	if (ret_value < 0)
		ft_perror(DUP_ERR);
	close(fd1);
	return (ret_value);
}

void	ft_make_pipe(t_info *info, int index)
{
	int	pipe_ret;

	pipe_ret = pipe(info->pipe_alpha);
	if (pipe_ret < 0)
		ft_error(PIPE_ERR);
	return ;
}

void child_process(t_process *process, t_state *state, t_info *info, int i)
{
	// printf("child i : %d\n", i);
	if (process->index == START)
	{
		// write(2, "START\n", 6);
		close(info->pipe_alpha[0]);
		ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);
	}
	else if (process->index == MIDDLE)
	{
		// write(2, "MIDDLE\n", 7);
		close(info->pipe_alpha[0]);
		ft_dup2(info->pre_pipe, STDIN_FILENO);
		ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);

	}
	else
	{
		// write(2, "END\n", 4);
		ft_dup2(info->pre_pipe, STDIN_FILENO);
	}
	redir_fd(info, process->redir);
	multi_total_cmd(process->cmd, state);
}

void parent_process(t_process *process, t_info *info, int i)
{
	// printf("parent i : %d\n", i);
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
		// printf("process : %d i : %d, info.number : %d\n", storage[i]->index,  i, info.number);
		if (storage[i]->index != END)
		{
			// printf("create pipe\n");
			ft_make_pipe(&info, i);
		}
		// printf("pre->pipe %d\n", info.pre_pipe);
		info.pid[i] = fork();
		if (info.pid[i])
			parent_process(storage[i], &info, i);
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
	t_info info;

	init_info(storage, &info);
	info.pid[0] = fork();
	if (info.pid[0])
		wait(NULL);
	else
	{
		redir_fd(&info, storage[0]->redir);
		single_total_cmd(storage[0]->cmd, state);
	}
	free(info.pid);
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