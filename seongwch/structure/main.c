#include "list.h"

int main()
{
	t_list *my;
	t_list *hi;
	t_process **mine;
	
	// my = shell_split("hi    <<     name");
	// show_list(my);
	// my = shell_split("hi    <<     name");
	// show_list(my);
	// my = shell_split("hi    <<     name");
	// show_list(my);
	// my = shell_split("hi    <<     name");
	// show_list(my);
	// my = shell_split("hi    <<     name");
	// show_list(my);
	// my = shell_split("hi    <<     name");
	// show_list(my);
	my = shell_split("a");
	free_list(my);
	my = shell_split("< <a.txt grep a | cat -e >> yes.a ; hi;|");
	show_list(my);
	printf("%d\n", my->pipe_num);
	// mine = cmd_storage(my);
	// free_process(mine);
	mine = cmd_storage(my);
	show_process(mine);


	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return 0;
}