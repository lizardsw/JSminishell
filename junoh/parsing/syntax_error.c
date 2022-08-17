/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:29:41 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 14:33:06 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// redir error 확인해줌. ex) < <
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

// pipe error 확인해줌. ex)  | echo
static int	check_pipe(t_process *process)
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

// syntax_error 확인해줌.
int	syntax_error(t_process **parsing)
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
