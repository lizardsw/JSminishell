/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:55:16 by seongwch          #+#    #+#             */
/*   Updated: 2022/07/25 12:31:04 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// str에 number만큼 strdup
char	*get_strdup(char *src, int number)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * number + 1);
	if (new == NULL)
		exit(1);
	while (i < number)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// 문자가 어떤 group인지 확인해준다.
int	check_group(char c)
{
	if (c == ' ')
		return (SPACES);
	else if (c == '<' || c == '>')
		return (REDIR);
	else if (c == '\'' || c == '\"')
		return (QUOTE);
	else if (c == '|')
		return (PIP);
	else if (c == '\0')
		return (ZERO);
	return (WORD);
}

// syntax_node에 token을 라벨링 시켜줌
void	label_token(t_node *ptr)
{
	char	*temp;

	temp = ptr->data;
	if (ptr->group == REDIR)
	{
		if (temp[0] == '<')
		{
			if (temp[1] == '<')
				ptr->token = RDRDIN;
			else
				ptr->token = RDIN;
		}
		else
		{
			if (temp[1] == '>')
				ptr->token = RDRDOUT;
			else
				ptr->token = RDOUT;
		}
	}
	else if (ptr->group == PIP)
		ptr->token = PIPE;
	else if (ptr->group == QUOTE || ptr->group == WORD)
		ptr->token = CMD;
}
