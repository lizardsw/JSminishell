/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:59:43 by junoh             #+#    #+#             */
/*   Updated: 2022/08/18 15:38:54 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_str(char *s1, char *s2)
{
	if (s2 == NULL)
		return (1);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)) && \
			ft_strlen(s1) == ft_strlen(s2))
		return (1);
	else
		return (0);
}

void	export_print_with_value(t_node *node)
{
	char	**split;
	char	*buf;

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
		printf("=\"");
		printf("%s", split[1]);
		printf("\"\n");
	}
	free_str(split);
	return ;
}

void	export_print(t_state *state)
{
	t_node	*node;

	node = state->env_lst->start;
	while (node != NULL)
	{
		if (!ft_strchr(node->data, '='))
			printf("declare -x %s\n", node->data);
		else
			export_print_with_value(node);
		node = node->next;
	}
	return ;
}
