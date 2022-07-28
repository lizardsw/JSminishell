#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "parsing.h"

// gcc -g -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include *.c libft.a 
// 위에 명령어를 통해 함수를 사용할 수 있다!!

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

int		main(int argc, char **argv, char **env)
{
	int				ret;
	char			*line;
	t_list			*list;
	t_process		**storage;
	t_state			state;

	signal(SIGINT, handler);
	state.env_lst = make_list_env(env);
	while (true)
	{
		line = readline("JSminishell> ");
		if (line)
		{
			ret = strcmp(line, "exit");
			if (ret)
				printf("output> %s\n", line);
			add_history(line);
			list = shell_split(line);
			show_list(list);
			if (list->state == GOOD)
			{
				storage = make_ast(list);
				show_process(storage);
				expand_ast(storage, &state);
				show_process(storage);
				system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
				if (syntax_error(storage) == -1)
				{
					printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
					printf("$$$$$$$syntax_error!$$$$$$$$$$\n");
					printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				}
				free_process(storage);
			}
			else if(list->state == ERROR)
			{
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
				printf("@@@@@@@@@@ QUOTE error!@@@@@@@@@@\n");
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

			}
			free_list(list);
			free(line);
			line = NULL;
			if (!ret)
				break ;
		}
		else
			return (1);
	}
	return (0);
}

/*
int main()
{
	t_process		**storage;
	t_list			*list;

	list = shell_split("e\"hi\"o hi");
	storage = make_ast(list);
	show_process(storage);

	return 0;
}
*/