#include "process.h"
#include <string.h>


void	setting_fd(int *pipe_fd)
{



}




int	main(int argc, char **argv, char **envp)
{
	int		i;
	pid_t pid[6];
	int	pipe1_fd[2];
	int	pipe2_fd[2];
	char buff[100];
	char	temp[100];

	pipe(pipe1_fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		// child
		dup2(pipe1_fd[1], STDOUT_FILENO);
		close(pipe1_fd[0]);
		close(pipe1_fd[1]);
	}
	else
	{
		// parent
		close(pipe1_fd[1]);
	}
	pipe(pipe2_fd);
	pid[1] = fork();
	if (pid[0] == 0)
	{
		// child
		dup2(pipe1_fd[0], STDIN_FILENO);
		dup2(pipe2_fd[1], STDOUT_FILENO);
		close(pipe1_fd[0]);
		close(pipe2_fd[1]);
		close(pipe2_fd[0]);
	}
	else
	{
		// parent

	}
	pipe(pipe1_fd);
	pid[2] = fork();
	if (pid[0] == 0)
	{
		// child
	
	}
	else
	{
		// parent

	}
	pipe(pipe2_fd);
	pid[3] = fork();
	if (pid[0] == 0)
	{
		// child

	}
	else
	{
		// parent

	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return 0;
}