#include "process.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	char *hi[4];

	hi[0] ="yes";
	hi[1] = "bye";
	hi[2] = "oh";
	hi[3] = NULL;
	execve("/usr/bin/env",&argv[1],hi);
}