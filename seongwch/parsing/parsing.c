#include "parsing.h"

int	parsing(t_process ***storage, t_state *state, char *line)
{
	t_list	*list;

	*storage = NULL;
	list = shell_split(line);
	// show_list(list);
	// printf("%d\n", list->state);
	if (list->state == GOOD | list->state == BLANK)
	{
		*storage = make_ast(list);
		// show_process(*storage);
		expand_ast(*storage, state);
		// show_process(*storage);
		if (syntax_error(*storage) == -1)
		{
			printf("syntax_error!\n");
			return (-1);
		}
	}
	else if (list->state == ERROR)
	{
		printf("QUOTE error!\n");
		return (-1);
	}
	free(list);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_state		state;
	t_process	**storage;
	char		*line;

	setting_terminal();
	signal_handler();
	state.env_lst = make_list_env(env);
	while (1)
	{
		line = readline("JSminishell> ");
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			exit(1);
		}
		add_history(line);
		if (parsing(&storage, &state, line) == 1)
		{
			// show_process(storage);
			pipe_main(storage, &state);
		}
		free_process(storage);
		free(line);
		// system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	}
	return 0;
}