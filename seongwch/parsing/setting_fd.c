#include "parsing.h"

int	open_outfile(char *file, int flag)
{
	int	open_ret;

	if (flag == RDOUT)
	{
		open_ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0000644);
		if (open_ret < 0)
			ft_perror(OUTFILE_OPEN_ERR);
	}
	else if (flag == RDRDOUT)
	{
		open_ret = open(file, O_APPEND | O_CREAT | O_WRONLY, 0000644);
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
		// you have to make heredoc
	}
	return (open_ret);
}

void close_file(t_info *info, int token)
{
	if (token == RDRDIN || token == RDIN)
	{
		if (info->fd_in != -2)
			close(info->fd_in);
	}
	else if (token == RDOUT || token == RDRDOUT)
	{
		if (info->fd_out != -2)
			close(info->fd_out);
	}
}

void	dup2_redir(t_info *info)
{
	if (info->fd_in > 0)
		ft_dup2(info->fd_in, STDIN_FILENO);
	if (info->fd_out > 0)
		ft_dup2(info->fd_out, STDOUT_FILENO);
}

void	redir_fd(t_info *info, t_list *redir)
{
	t_node	*ptr;

	ptr = redir->start;
	while (ptr != NULL)
	{
		close_file(info, ptr->token);
		if (ptr->token == RDIN)
			info->fd_in = open_infile(ptr->next->data, RDIN);
		else if (ptr->token == RDOUT)
			info->fd_out = open_outfile(ptr->next->data, RDOUT);
		else if (ptr->token == RDRDIN)
			info->fd_in = open_infile(ptr->next->data, RDRDIN);
		else if (ptr->token == RDRDOUT)
			info->fd_out = open_outfile(ptr->next->data, RDRDOUT);
		ptr = ptr->next->next;
	}
	dup2_redir(info);
}