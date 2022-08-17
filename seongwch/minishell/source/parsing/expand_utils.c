/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:22:40 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 16:06:38 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	position_except(char **storage, char *front_str, char *str, int i)
{
	char	*temp;
	if (str[i] == '?') // $? 처리해주는 부분!
	{
		temp = ft_itoa(errno);
		printf("%d %s\n", errno, temp);
		*storage = null_strjoin(front_str, temp);
		free(front_str);
		free(temp);
		return (i + 1);
	}
	if (str[i] == '$')
	{
		*storage = null_strjoin(front_str, "");
		free(front_str);
		return (i + 1);
	}
	return (0);
}

static void	position_back_str(char *str, char **back_str, int i, int is_dquote)
{
	if ((str[i] == '\'' || str[i] == '\"') && is_dquote != 1)
		*back_str = NULL;
	else if ((str[i] == ' ' || str[i] == '\0') \
					|| (str[i] == '\'' || str[i] == '\"') && is_dquote == 1)
		*back_str = ft_strdup("$");
}

int	position_expand(char **storage, char *str, t_state *state, int is_dquote)
{
	int		i;
	char	*key;
	char	*back_str;
	char	*front_str;

	i = 1;
	front_str = *storage;
	while (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' \
				&& str[i] != '\0' && str[i] != '$' && str[i] != '?')
		i++;
	if (str[i] == '?' || str[i] == '$')
		return (position_except(storage, front_str, str, i));
	key = get_strdup(&str[1], i - 1);
	if (key[0] == '\0')
		position_back_str(str, &back_str, i, is_dquote);
	else
		back_str = get_value(state->env_lst, key);
	*storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	free(key);
	return (i);
}

int	dquote_expand(char **str_storage, char *str, t_state *state)
{
	char	*front_str;
	char	*back_str;
	int		i;
	int		j;

	i = 1;
	while (str[i] != '\"')
	{
		front_str = *str_storage;
		j = 0;
		while (str[i + j] != '$' && str[i + j] != '\"')
			j++;
		back_str = get_strdup(&str[i], j);
		*str_storage = null_strjoin(front_str, back_str);
		free(front_str);
		free(back_str);
		if (str[i + j] == '$')
			j += position_expand(str_storage, &str[i + j], state, 1);
		i += j;
	}
	i++;
	return (i);
}
