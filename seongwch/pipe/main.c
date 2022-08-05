#include "process.h"
#include <string.h>


int	ft_dup2(int fd1, int fd2)
{
	int	ret_value;

	ret_value = dup2(fd1, fd2);
	close(fd1);
	return (ret_value);
}

void	ft_make_pipe(t_info *info, int index)
{
	int	pipe_ret;

	if (index % 2 == 0)
	{
		pipe_ret = pipe(info->pipe_alpha);
	}
	else
	{
		pipe_ret = pipe(info->pipe_beta);
	}
	return ;
}

void child_process(t_info *info, int i)
{
	if (i % 2 == 0)
	{
		close(info->pipe_alpha[0]);
		if (i != 0)
			ft_dup2(info->pipe_beta[0], STDIN_FILENO);
		if (i != END)
			ft_dup2(info->pipe_alpha[1], STDOUT_FILENO);
		
		execute_cmd(info->argv[i], info->envp);
	}
	else
	{
		close(info->pipe_beta[0]);
		ft_dup2(info->pipe_alpha[0], STDIN_FILENO);
		if (i != END)
			ft_dup2(info->pipe_beta[1], STDOUT_FILENO);
			
		execute_cmd(info->argv[i], info->envp);
	}
}

void parent_process(t_info *info, int i)
{
	if (i == 0)
	{
		close(info->pipe_alpha[1]);
		if (i != 0 || i != END)
			close(info->pipe_beta[0]);
	}
	else
	{
		close(info->pipe_beta[1]);
		if (i != END)
			close(info->pipe_alpha[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	pid_t pid[7];
	t_info info;
	while (i < 7)
	{
		if (i != END)
			ft_make_pipe(&info, i);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			// child

		}
		else
		{
			// parent
		}
		i++;
	}
}