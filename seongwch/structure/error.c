#include "list.h"



int	check_redir(t_process *process)
{
	t_node *ptr;

	ptr = process->redir->start;
	while (ptr != NULL)
	{
		if (ptr->group == REDIR)
		{
			if(ptr->next == NULL)
				return (-1);
			else if (ptr->next->group == REDIR)
				return (-1);
		}
		ptr = ptr->next;
	}
	return (1);
}

int	check_pipe(t_process *process)
{
	int	redir_num;
	int	cmd_num;
	
	if (process->token == PIPE)
	{
		redir_num = process->redir->number;
		cmd_num = process->cmd->number;
		if (redir_num == 0 && cmd_num == 0)
			return (-1);
	}
	return (1);
}

int syntax_error(t_process **parsing)
{
	int	i;
	int	check;
	
	i = 0;
	while (parsing[i] != NULL)
	{
		if (check_redir(parsing[i]) == -1)
			return (-1);
		if (check_pipe(parsing[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}