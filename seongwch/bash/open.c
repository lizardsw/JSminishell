#include <stdio.h>
#include <fcntl.h>




int main()
{
	int fd;

	fd = open("a.txt", O_WRONLY | O_TRUNC | O_CREAT, 0000644);
	printf("%d\n", fd);

	return 0;
}
