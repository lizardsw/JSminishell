#include "parsing.h"

int main(int argc, char **argv, char **env)
{
	int		i;
	char *hi;
	char	*storage;

	t_state state;
	t_node node;

	state.env_lst = make_list_env(env);
	hi = NULL;
	storage = NULL;
	node.data = ft_strdup("\"$$$\"");
	expand_syntax(&node, &state);
	printf("%s", node.data);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return 0;
}