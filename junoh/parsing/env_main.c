#include "parsing.h"


int main(int argc, char **argv, char **env)
{
	int	i;

	i  = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("\n");
	t_list	*ptr;

	ptr = make_list_env(env);
	show_list(ptr);

	return 0;
}