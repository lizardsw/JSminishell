/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:25:45 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 16:09:49 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_process **storage, t_info *info)
{
	t_process	*ptr;
	int			i;

	i = 0;
	while (storage[i] != NULL)
		i++;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (info->pid == NULL)
		exit(1);
	info->pid[0] = 1;
	info->number = i;
	info->pre_pipe = -1;
	info->fd_in = -2;
	info->fd_out = -2;
}

void	pipe_main(t_process **storage, t_state *state)
{
	if (storage[0]->token == PIPE)
		multi_process(storage, state);
	else
		single_process(storage, state);
}
