#include "process.h"



void	setting_fd(int *pipe_fd)
{



}




int	main(int argc, char **argv, char **envp)
{
	int		i;
	pid_t pid;
	int	pipe1_fd[2];
	int	pipe2_fd[2];
	char buff[100];

	pipe(pipe1_fd);
	pipe(pipe2_fd);
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe1_fd[PIPE_IN], STDOUT);
		write(STDOUT, "hi!", 4);
		exit(1);
	}
	else
	{
		wait(NULL);
		// dup2(pipe1_fd[PIPE_OUT], STDIN);
		// i = read(STDIN, buff, 100);
		// buff[i] = '\0';
		// // write(STDOUT, buff, i);
		// dup2(pipe2_fd[PIPE_IN], STDOUT);
	
		// write(STDOUT, buff, i);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe1_fd[PIPE_OUT], STDIN);
		dup2(pipe1_fd[PIPE_IN], STDOUT);
		i = read(STDIN, buff, 100);
		buff[i] = '\0';
		write(STDOUT, buff, i);
		exit(1);
	}
	else
	{
		wait(NULL);
		dup2(pipe1_fd[PIPE_OUT], STDIN);
		// dup2(pipe2_fd[PIPE_OUT], STDOUT);
		i = read(STDIN, buff, 100);
		buff[i] = '\0';
		write(STDOUT, buff, i);
	}
	// pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(pipe2_fd[PIPE_OUT], STDIN);
	// 	dup2(pipe1_fd[PIPE_IN], STDOUT);
	// 	i = read(STDIN, buff, 100);
	// 	buff[i] = '\0';
	// 	write(STDOUT, buff, i);
	// 	exit(1);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	dup2(pipe1_fd[PIPE_OUT], STDIN);
	// 	i = read(STDIN, buff, 100);
	// 	buff[i] = '\0';
	// 	write(STDOUT, buff, i);
	// 	printf("부모 프로세스\n");
	// }





	return 0;
}