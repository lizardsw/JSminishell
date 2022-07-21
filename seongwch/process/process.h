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





#endif 