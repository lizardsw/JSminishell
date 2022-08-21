/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:33:43 by junoh             #+#    #+#             */
/*   Updated: 2022/08/21 16:03:34 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_key_value(char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * 3);
	if (new == NULL)
		exit(1);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		new[0] = ft_strdup(str);
		new[1] = NULL;
	}
	else
	{
		new[0] = get_strdup(str, i);
		if (str[ft_strlen(str) - 1] == '=')
			new[1] = ft_strdup("");
		else
			new[1] = ft_strdup(&str[i + 1]);
	}
	new[2] = NULL;
	return (new);
}

char	*get_value(t_list *env, char *key)
{
	char	**split;
	char	*value;
	t_node	*ptr;

	value = NULL;
	ptr = env->start;
	while (ptr != NULL)
	{
		split = split_key_value(ptr->data);
		// if (!ft_strncmp(key, split[0], (int)ft_strlen(key)))
		if (cmd_compare(key, split[0]) == 0)
		{
			value = ft_strdup(split[1]);
			free_str(split);
			return (value);
		}
		free_str(split);
		split = NULL;
		ptr = ptr->next;
	}
	return (value);
}

char	**make_char_env(t_list *list)
{
	t_node		*ptr;
	char		**new;
	int			i;

	i = 0;
	ptr = list->start;
	new = (char **)malloc(sizeof(char *) * (list->number + 1));
	if (new == NULL)
		exit(1);
	while (ptr != NULL)
	{
		new[i] = ft_strdup(ptr->data);
		i++;
		ptr = ptr->next;
	}
	new[i] = NULL;
	return (new);
}

t_list	*make_list_env(char **env, t_state *state)
{
	t_list	*new;
	int		i;

	i = 0;
	new = new_list();
	while (env[i] != NULL)
	{
		push_node_back(new, new_node(env[i]));
		i++;
	}
	state->old_pwd = NULL;
	state->pwd = NULL;
	env[i] = NULL;
	return (new);
}
