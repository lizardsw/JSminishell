#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <string.h>


void handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
	{
		printf("r1_error!\n");
		exit(1);
	} 
	rl_replace_line("", 1);
	rl_redisplay();
}

void signal_handler()
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void setting_terminal()
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main()
{
	char	*line;

	setting_terminal();
	signal_handler();
	while (1)
	{
		line = readline("JSminishell > ");
		if (line ==NULL)
		{
			write(1, "exit\n", 6);
			exit(1);
		}
		add_history(line);
	}
}