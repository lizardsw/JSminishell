/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:42:08 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/16 20:05:30 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_outfile(char *file, int flag, int pid)
{
	int	open_ret;

	if (flag == RDOUT)
	{
		open_ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0000644);
		if (open_ret < 0 && pid != 1)
			ft_perror(OUTFILE_OPEN_ERR);
		else if (open_ret < 0 && pid == 1)
			ft_no_exit_perror(OUTFILE_OPEN_ERR);
	}
	else if (flag == RDRDOUT)
	{
		open_ret = open(file, O_APPEND | O_CREAT | O_WRONLY, 0000644);
		if (open_ret < 0 && pid != 1)
			ft_perror(OUTFILE_OPEN_ERR);
		else if (open_ret < 0 && pid == 1)
			ft_no_exit_perror(OUTFILE_OPEN_ERR);
	}
	return (open_ret);
}

int	open_infile(t_node *node, int flag, int pid)
{
	int	open_ret;

	if (flag == RDIN)
	{
		open_ret = open(node->data, O_RDONLY);
		if (open_ret < 0 && pid != 1)
			ft_perror(INFILE_OPEN_ERR);
		else if (open_ret < 0 && pid == 1)
			ft_no_exit_perror(INFILE_OPEN_ERR);
	}
	else if (flag  == RDRDIN)
	{
		open_ret = node->group;
		if (open_ret < 0 && pid != 1)
			ft_perror(INFILE_OPEN_ERR);
		else if (open_ret < 0 && pid == 1)
			ft_no_exit_perror(INFILE_OPEN_ERR);
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

int	redir_fd(t_info *info, t_list *redir)
{
	t_node	*ptr;

	ptr = redir->start;
	while (ptr != NULL)
	{
		close_file(info, ptr->token);
		if (ptr->token == RDIN)
			info->fd_in = open_infile(ptr->next, RDIN, \
			info->pid[0]);
		else if (ptr->token == RDOUT)
			info->fd_out = open_outfile(ptr->next->data, RDOUT, info->pid[0]);
		else if (ptr->token == RDRDIN)
			info->fd_in = open_infile(ptr->next, RDRDIN, \
			info->pid[0]);
		else if (ptr->token == RDRDOUT)
			info->fd_out = open_outfile(ptr->next->data, RDRDOUT, info->pid[0]);
		if (info->fd_out == -1 || info->fd_in == -1)
			return (-1);
		ptr = ptr->next->next;
	}
	dup2_redir(info);
	return (1);
}