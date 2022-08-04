#include "process.h"
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv, char **env)
{
	int fd;

	char buff[100];
	char *hi = "hi";
	char *bye = "bye";
	buff[0] = 'a';
	buff[1] = '\0';

	strcat(buff, bye);
	printf("%s\n", hi);
	printf("%s\n", buff);

	// fd = open("./output.txt", O_APPEND | O_CREAT | O_WRONLY, 0000644);
	// // fd = open("./output.txt", O_WRONLY);
	// printf("%d\n",fd);
	// dup2(fd, STDOUT_FILENO);
	// printf("hello!\n");
	// write(1, "me!", 2);
	// return 0;
}