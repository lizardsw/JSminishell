#include "parsing.h"


int main(int argc, char **argv, char **env)
{
	int		i;
	char *hi;
	char	*storage;

	t_state state;

	state.env_lst = make_list_env(env);
	hi = NULL;
	storage = NULL;
	// i = cmd_expand(&storage, "hello!");
	// printf("return : %d storage : %s\n", i, storage);
	// i = cmd_expand(&storage, "$s");
	// printf("return : %d storage : %s\n", i, storage);
	// i = position_expand(&storage, "$PAH", &state);
	// printf("return : %d storage : %s\n", i, storage);
	i = dquote_expand(&storage, "\"aaa$USER $USER\"", &state);
	printf("return : %d storage : %s\n", i, storage);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return 0;
}