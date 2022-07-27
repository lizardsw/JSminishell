/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:33:43 by junoh             #+#    #+#             */
/*   Updated: 2022/07/27 14:45:28 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**split_key_value(char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * 3);
	if (new == NULL)
		exit(1);
	while (str[i] != '=')
		i++;
	new[0] = get_strdup(str, i + 1);
	new[1] = ft_strdup(&str[i + 1]);
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
		if (!ft_strncmp(key, split[0], (int)ft_strlen(key)))
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

t_list	*make_list_env(char **env)
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
	env[i] = NULL;
	return (new);
}
