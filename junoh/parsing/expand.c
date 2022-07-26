#include "parsing.h"








static void	expand_syntax(t_list *list, t_state *state)
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