/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:59:43 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 20:32:10 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    export_print_with_value(t_state *state, t_node *node)
{
	char    **split;
	char    *buf;
	
	buf = NULL;
	split = split_key_value(node->data);
	if (split[1] == NULL)
	{
		buf = ft_strjoin(node->data, "\"\"");
		printf("declare -x %s\n", buf);
		free(buf);
	}
	else
	{
		printf("declare -x %s", split[0]);
		printf("\"");
		printf("%s", split[1]);
		printf("\"\n");
	}
	return ;
}

void    export_print(t_state *state)
{
	t_node  *node;
	
	node = state->env_lst->start;
	while (node != NULL)
	{
		if (!ft_strchr(node->data, '='))
			printf("declare -x %s\n", node->data);
		else
			export_print_with_value(state, node);
		node = node->next;
	}
	return ;
}