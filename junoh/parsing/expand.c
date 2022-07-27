#include "parsing.h"

static void	expand_syntax(t_node *node, t_state *state)
{
	char	*storage;
	int		i;
	int		j;

	i = 0;
	storage = NULL;
	while (node->data[i] != '\0')
	{
		j = 0;
		j += cmd_expand(storage, &node->data[i]);
		if (node->data[i + j] == '\'')
			j += squote_expand(storage, &node->data[i + j]);
		else if (node->data[i + j] == '\"')

		else if (node->data[i + j] == '$')
		{}
		else if (node->data[i + j] == '\0')
		{}
		i++;
	}
}

static void	classify_token(t_list *list, t_state *state)
{
	t_node	*ptr;

	ptr = list->start;
	while (ptr != NULL)
	{
		if (ptr->group == QUOTE)
		{

		}
		else if (ptr->group == WORD)
		{

		}
		ptr = ptr->next;
	}

}

void	expand_ast(t_process **ast, t_state *state)
{
	int	i;

	i = 0;
	while (ast[i] != NULL)
	{
		expand_syntax(ast[i]->redir, state);
		expand_syntax(ast[i]->cmd, state);		
		i++;
	}
}