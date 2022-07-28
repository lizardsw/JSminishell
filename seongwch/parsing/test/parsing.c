#include "parsing.h"

int	parsing(t_process **storage, t_state *state, char *line)
{
	t_list	*list;

	storage = NULL;
	list = shell_split(line);
	if (list->state == GOOD)
	{
		storage = make_ast(list);
		expand_ast(storage, state);
		if (syntax_error(storage) == -1)
		{
			printf("syntax_error!\n");
			return (-1);
		}
	}
	else if (list->state = ERROR)
	{
		printf("QUOTE error!\n");
		return (-1);
	}
	free(list);
	return (1);
}


void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
	{
		printf("rl_one_new_line = -1!\n");
		exit(1);
	}
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_state		state;
	t_process	**storage;
	char		*line;

	signal(SIGINT, handler);
	state.env_lst = make_list_env(env);
	while (1)
	{
		line = readline('JSminishell');
		add_history(line);
		if (parsing(storage, &state, line) == 1)
		{
			
		}
		free_process(storage);
		free(line);
	}

}