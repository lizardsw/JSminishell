#include "parsing.h"

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

void child_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(2, "child!\n", 7);
// 	write(STDOUT_FILENO, "\n", 1);
// 	printf("handler!\n");
// 	if (rl_on_new_line() == -1)
// 	{
// 		printf("r1_error!\n");
// 		exit(1);
// 	} 
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// }
}

void signal_handler()
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void child_signal_handler()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void setting_terminal()
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
