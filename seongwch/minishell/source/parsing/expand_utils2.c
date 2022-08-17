/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_uils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:45:47 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 13:46:59 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	cmd_expand(char **str_storage, char *str)
{
	char	*front_str;
	char	*back_str;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0' && str[i] != '$')
			i++;
	front_str = *str_storage;
	back_str = get_strdup(str, i);
	*str_storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	return (i);
}

int	squote_expand(char **str_storage, char *str)
{
	char	*front_str;
	char	*back_str;
	int		i;

	front_str = *str_storage;
	i = 1;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	back_str = get_strdup(&str[1], i - 1);
	*str_storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	return (i);
}
