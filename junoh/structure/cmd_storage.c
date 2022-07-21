#include "list.h"


void	show_process(t_process **ptr)
{
	t_list	*redir;
	t_list	*cmd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("~~~~~~~~~~~~~~~~~~~\n");
	printf("-------------------\n");
	while (ptr[i] != NULL)
	{
		j = 0;
		redir = ptr[i]->redir;
		cmd = ptr[i]->cmd;
		printf("process : token(%d) index(%d)\n", ptr[i]->token, ptr[i]->index);
		printf("*redir : %d\n", redir->number);
		show_list(redir);
		printf("*cmd : %d\n", cmd->number);
		show_list(cmd);
		printf("-------------------\n");
		i++;
	}
	printf("~~~~~~~~~~~~~~~~~~~\n");

}

t_process *new_process(void)
{
	t_process *new;

	new = (t_process *)malloc(sizeof(t_process));
	if (new == NULL)
		exit(1);
	new->redir = new_list();
	new->cmd = new_list();
	new->token = 0;
	return (new);
}

t_process **new_storage(int pipe_num)
{
	t_process **new;
	int			i;
	
	i = 0;
	new = (t_process **)malloc(sizeof(t_process *) * (pipe_num + 2));
	if (new == NULL)
		exit(1);
	while (i < pipe_num + 1)
	{
		new[i] = new_process();
		if (i == 0)
			new[i]->index = START;
		else if (i == pipe_num)
			new[i]->index = END;
		else
			new[i]->index = MIDDLE;
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	label_token(t_node *ptr)
{
	char	*temp;

	temp = ptr->data;
	if (ptr->group == REDIR)
	{
		if (temp[0] == '<')
		{
			if(temp[1] == '<')
				ptr->token = RDRDIN;
			else
				ptr->token = RDIN;
		}
		else
		{
			if(temp[1] == '>')
				ptr->token = RDRDOUT;
			else
				ptr->token = RDOUT;
		}
	}
	else if (ptr->group == PIP)
	{
		if (temp[0] == '|')
			ptr->token = PIPE;
		else
			ptr->token = SCOLON;
	}
	else if (ptr->group == QUOTE)
		ptr->token = CMD;
	else if (ptr->group == WORD)
		ptr->token = CMD;
}

void	mv_redir_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	label_token(ptr);
	push_node_back(prc->redir, ptr);
	if (split->start != NULL && split->start->group != PIP && split->start->group != REDIR)
	{
		ptr = pop_node_front(split);
		label_token(ptr);
		push_node_back(prc->redir, ptr);
	}
}

void	mv_cmd_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	label_token(ptr);
	push_node_back(prc->cmd, ptr);
}

void	mv_pip_syn(t_process *prc, t_list *split)
{
	t_node	*ptr;

	ptr = pop_node_front(split);
	if (ptr->data[0] == '|')
		prc->token = PIPE;
	else if (ptr->data[0] == ';')
		prc->token = SCOLON;
	free_node(ptr);
}

t_process **cmd_storage(t_list *list)
{
	t_process **storage;
	t_node		*ptr;
	int			i;

	i = 0;
	ptr = list->start;
	storage = new_storage(list->pipe_num);
	while (ptr != NULL)
	{
		if (ptr->group == REDIR)
			mv_redir_syn(storage[i], list);
		else if (ptr->group == WORD | ptr->group == QUOTE)
			mv_cmd_syn(storage[i], list);
		else if (ptr->group == PIP)
		{
			mv_pip_syn(storage[i], list);
			i++;
		}
		ptr = list->start;
	}
	return storage;
}
