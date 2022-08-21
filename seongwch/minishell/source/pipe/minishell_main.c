/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:09:40 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/21 16:02:26 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	parsing_util(t_process ***storage, t_state *state, t_list *list)
{
	if (list->state == GOOD)
	{
		*storage = make_ast(list);
		expand_ast(*storage, state);
		if (syntax_error(*storage) == -1)
		{
			free_process(*storage);
			ft_no_exit_error(SYN_ERR);
			return (-1);
		}
	}
	else if (list->state == ERROR)
	{
		ft_no_exit_error(QUOTE_ERR);
		return (-1);
	}
	return (1);
}

static	int	parsing(t_process ***storage, t_state *state, char *line)
{
	t_list	*list;

	*storage = NULL;
	if (ft_strlen(line) < 1)
		return (-1);
	add_history(line);
	list = shell_split(line);
	if (parsing_util(storage, state, list) == -1)
	{
		free_list(list);
		return (-1);
	}
	free_list(list);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_state		state;
	t_process	**storage;
	char		*line;

	(void)argc;
	(void)argv;
	setting_terminal();
	signal_handler();
	state.env_lst = make_list_env(env, &state); // &state 추가
	while (1)
	{
		line = readline("JSminishell> ");
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		if (parsing(&storage, &state, line) == 1)
		{
			pipe_main(storage, &state);
			free_process(storage);
		}
		free(line);
	}
	return (0);
}
