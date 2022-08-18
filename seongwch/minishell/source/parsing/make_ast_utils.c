/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:06:06 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 15:27:50 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*new_process(void)
{
	t_process	*new;

	new = (t_process *)malloc(sizeof(t_process));
	if (new == NULL)
		exit(1);
	new->redir = new_list();
	new->cmd = new_list();
	new->token = 0;
	return (new);
}

t_process	**new_storage(int pipe_num)
{
	t_process	**new;
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
