#include <unistd.h>
#include <stdio.h>


int main()
{
	char buff[100];
	char *temp;

	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	chdir("/Users/seongwch/Desktop");
	temp = getcwd(NULL, 0);
	printf("%s\n", temp);

	return 0;
}