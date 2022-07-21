#include "list.h"

void	free_node(t_node *ptr)
{
	free(ptr->data);
	free(ptr);
}

void	free_list(t_list *list)
{
	t_node	*ptr;
	t_node	*temp;

	ptr = list->start;
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free_node(temp);
	}
	free(list);
}

void	free_process(t_process **prc)
{
	int i;

	i = 0;
	while (prc[i] != NULL)
	{
		free_list(prc[i]->redir);
		free_list(prc[i]->cmd);
		free(prc[i]);
		i++;
	}
	free(prc);
}