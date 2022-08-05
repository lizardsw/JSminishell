#ifndef PROCESS_H
# define PROCESS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

enum std_streams
{
	PIPE_IN = 1,
	PIPE_OUT = 0,
	STDIN = 0,
	STDOUT = 1
};

typedef struct s_info
{
	int fd_in;
	int fd_out;
	int pipe_alpha[2];
	int pipe_beta[2];
	pid_t	*pid;
}	t_info ;


#endif 