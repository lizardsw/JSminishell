/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:26:12 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/05 18:11:15 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand_syntax(t_node *node, t_state *state)
{
	char	*storage;
	int		i;
	int		j;

	i = 0;
	storage = NULL;
	while (node->data[i] != '\0')
	{
		j = 0;
		j += cmd_expand(&storage, &node->data[i]);
		if (node->data[i + j] == '\'')
			j += squote_expand(&storage, &node->data[i + j]);
		else if (node->data[i + j] == '\"')
			j += dquote_expand(&storage, &node->data[i + j], state);
		else if (node->data[i + j] == '$')
			j += position_expand(&storage, &node->data[i + j], state, 0);
		else if (node->data[i + j] == '\0')
			j++;
		i += j;
		if (i > strlen(node->data))
			break;
	}
	free(node->data);
	node->data = storage;
}

static void	classify_token(t_list *list, t_state *state)
{
	t_node	*ptr;

	ptr = list->start;
	while (ptr != NULL)
	{
		if (ptr->group == QUOTE || ptr->group == WORD)
			expand_syntax(ptr, state);
		ptr = ptr->next;
	}
}

void	expand_ast(t_process **ast, t_state *state)
{
	int	i;

	i = 0;
	while (ast[i] != NULL)
	{
		classify_token(ast[i]->redir, state);
		classify_token(ast[i]->cmd, state);
		i++;
	}
}
