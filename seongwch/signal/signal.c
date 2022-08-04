#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

// void	hi(int signum)
// {
// 	if (signum != SIGINT)
// 		return ;
// 	write(STDOUT_FILENO, "\n", 1);
// 	if (rl_on_new_line() == -1)
// 	{
// 		printf("rl_one_new_line = -1!\n");
// 		exit(1);
// 	}
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// }

void	bye()
{
	printf("bye\n");

}


int	main()
{
	//tcgetattr(int fd, struct termios *termios_p);
	struct termios hi;
	int		fd;
	tcgetattr(1, &hi);
	printf("%lu\n",hi.c_cflag);
	hi.c_lflag &= ~(ICANON | ECHOCTL);

	tcgetattr(0, &hi);
	printf("%lu\n",hi.c_lflag);

	tcgetattr(0, &hi);
	printf("%lu\n",hi.c_iflag);

	tcgetattr(0, &hi);
	printf("%lu\n",hi.c_lflag);
	
	write(1, "hi", 2);
	write(1, "\b", 2);
	// printf("\b\b");

	// tcgetattr(1, &hi);
	// printf("%s\n",hi.c);

	return 0;
}