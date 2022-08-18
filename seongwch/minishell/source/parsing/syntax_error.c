/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:29:41 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 15:42:28 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir(t_process *process)
{
	t_node	*ptr;

	ptr = process->redir->start;
	while (ptr != NULL)
	{
		if (ptr->group == REDIR)
		{
			if (ptr->next == NULL)
				return (-1);
			else if (ptr->next->group == REDIR)
				return (-1);
		}
		ptr = ptr->next;
	}
	return (1);
}

static int	check_pipe(t_process *process, int i)
{
	int	redir_num;
	int	cmd_num;

	if (i != 0)
	{
		redir_num = process->redir->number;
		cmd_num = process->cmd->number;
		if (redir_num == 0 && cmd_num == 0)
			return (-1);
	}
	if (process->token == PIPE)
	{
		redir_num = process->redir->number;
		cmd_num = process->cmd->number;
		if (redir_num == 0 && cmd_num == 0)
			return (-1);
	}
	return (1);
}

int	syntax_error(t_process **parsing)
{
	int	i;

	i = 0;
	while (parsing[i] != NULL)
	{
		if (check_redir(parsing[i]) == -1)
			return (-1);
		if (check_pipe(parsing[i], i) == -1)
			return (-1);
		i++;
	}
	return (1);
}
