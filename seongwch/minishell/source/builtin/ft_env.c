/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:42:25 by junoh             #+#    #+#             */
/*   Updated: 2022/08/18 15:05:58 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_state *state, t_node *cmd_node)
{
	t_node	*node;

	if (cmd_node->next != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd_node->next->data);
		return (-1);
	}
	else
	{
		node = state->env_lst->start;
		while (node != NULL)
		{
			if (ft_strchr(node->data, '='))
				printf("%s\n", node->data);
			node = node->next;
		}
		return (0);
	}
}
