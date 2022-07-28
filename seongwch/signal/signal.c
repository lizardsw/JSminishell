#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	hi(int signum)
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

void	bye()
{
	printf("bye\n");

}


int	main()
{
	//tcgetattr(int fd, struct termios *termios_p);
	termios me;

	return 0;
}