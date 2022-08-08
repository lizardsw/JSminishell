#include "parsing.h"

void handler(int signum)
{
	pid_t	pid;

	if (signum != SIGINT)
		return ;
	pid = waitpid(-1, NULL, WNOHANG);
	if (pid == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
		{
			printf("r1_error!\n");
			exit(1);
		} 
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		write(STDOUT_FILENO, "^C\n", 3);
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
