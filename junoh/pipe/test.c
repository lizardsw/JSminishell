#include "process.h"


int main(int argc, char **argv, char **env)
{
	int	i;

	i  = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}