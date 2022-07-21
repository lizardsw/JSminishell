#include <readline/readline.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	int fd1;
	int	temp;
	char	*str;

	fd = open("./hi.txt", O_RDWR);
	fd1 = open("./out.txt", O_WRONLY);
	while (1)
	{
		str = readline("intput : ");
		printf("%s\n", str);
		temp = rl_on_new_line();
		printf("temp : %d\n", temp);
	}

	return 0;
}