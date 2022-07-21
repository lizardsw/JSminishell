#include "list.h"

void	show_list(t_list *list)
{
	t_node	*ptr;

	// printf("-------------------\n");
	ptr = list->start;
	if (ptr == NULL)
	printf("EMPTY! list");
	while (ptr != NULL)
	{
		printf("[%s gt(%d,%d)] ", ptr->data, ptr->group, ptr->token);
		ptr = ptr->next;
	}
	printf("\n");
	// printf("\n-------------------\n");
}

t_list *new_list(void)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		exit(1);
	new->start = NULL;
	new->end = NULL;
	new->number = 0;
	new->pipe_num = 0;
	new->state = GOOD;
	return (new);
}

t_node *new_node(char *str)
{
	t_node *new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		exit(1);
	new->next = NULL;
	new->prev = NULL;
	new->data = ft_strdup(str);
	new->token = -1;
	new->group = -1;
	return (new);
}

void	push_node_back(t_list *list, t_node *node)
{
	t_node	*ptr;
	
	list->number++;
	if (list->number == 1)
	{
		list->start = node;
		list->end = node;
		return;
	}
	ptr = list->end;
	node->prev = ptr;
	ptr->next = node;
	list->end = node;
}

void	push_node_front(t_list *list, t_node *node)
{
	t_node	*ptr;

	list->number++;
	if (list->number == 1)
	{
		list->start = node;
		list->end = node;
		return;
	}
	ptr = list->start;
	ptr->prev = node;
	node->next = ptr;
	list->start = node;
}

t_node *pop_node_back(t_list *list)
{
	t_node *ptr;

	ptr = list->end;
	if(list->number == 0)
		return NULL;
	list->number--;
	if(list->number == 0)
	{
		list->start = NULL;
		list->end = NULL;
		return ptr;
	}
	list->end = ptr->prev;
	ptr->prev->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

t_node *pop_node_front(t_list *list)
{
	t_node *ptr;

	ptr = list->start;
	if(list->number == 0)
		return NULL;
	list->number--;
	if(list->number == 0)
	{
		list->start = NULL;
		list->end = NULL;
		return ptr;
	}
	list->start = ptr->next;
	ptr->next->prev = NULL;
	ptr->next = NULL;
	return (ptr);
}

