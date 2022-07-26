/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:06:06 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/21 17:27:49 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	show_process(t_process **ptr)
{
	t_list	*redir;
	t_list	*cmd;
	int		i;
	int		j;

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
