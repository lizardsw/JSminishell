#include "parsing.h"

int	open_outfile(char *file, int flag)
{
	int	open_ret;

	if (flag == RDOUT)
	{
		open_ret = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (open_ret < 0)
			ft_perror(OUTFILE_OPEN_ERR);
	}
	else if (flag == RDRDOUT)
	{
		open_ret = opsen(file, O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (open_ret < 0)
			ft_perror(OUTFILE_OPEN_ERR);
	}
	return (open_ret);
}

int	open_infile(char *file, int flag)
{
	int	open_ret;

	if (flag == RDIN)
	{
		if (access(file, F_OK) != 0)
			ft_perror(INFILE_OPEN_ERR);
		open_ret = open(file, O_RDONLY);
		if (open_ret < 0)
			ft_perror(INFILE_OPEN_ERR);
	}
	else if (flag  == RDRDIN)
	{

	}
	return (open_ret);
}

void close_file(int *fd, int token)
{
	if (token == RDRDIN || token == RDIN)
		if (fd[STDIN_FILENO] != 0)
			close(fd[STDIN_FILENO]);
	else if (token == RDOUT || token == RDRDOUT)
		if (fd[STDOUT_FILENO] != 1)
			close(fd[STDOUT_FILENO]);
}

void	setting_fd(int *fd, t_list *redir)
{
	t_node	*ptr;

	ptr = redir->start;
	while (ptr != NULL)
	{
		close_file(fd, ptr->token);
		if (ptr->token == RDIN)
			fd[STDIN_FILENO] = open_infile(ptr->next->data, RDIN);
		else if (ptr->token == RDOUT)
			fd[STDOUT_FILENO] = open_outfile(ptr->next->data, RDOUT);
		else if (ptr->token == RDRDIN)
			fd[STDIN_FILENO] = open_infile(ptr->next->data, RDRDIN);
		else if (ptr->token == RDRDOUT)
			fd[STDOUT_FILENO] = open_outfile(ptr->next->data, RDRDOUT);
		ptr = ptr->next->next;
	}
}


void multi_process(t_process **storage, t_state *state)
{
	int	i;
	t_info info;

	i = 0;
	while (storage[i] != NULL)
	{
		fd[STDIN_FILENO] = 0;
		fd[STDOUT_FILENO] = 1;
		setting_pipe(fd, )
		setting_fd(fd, storage[i]->redir)
	}


}

void single_process(t_process *storage, t_state *state)
{
	int	fd[2];

	setting_fd(fd, storage->redir);
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
}

void pipe_main(t_process **storage, t_state *state)
{
	int i;

	i = 0;
	if (storage[0]->token == PIPE)
	{

	}
	else
	{

	}
}