/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:03:02 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 20:32:24 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 이전 함수에서 dup2(fd, STDOUT) 이 되어있음

int ft_pwd(t_list *cmd_list, t_state *state)
{
	char    *str;

	(void)(cmd_list);
	(void)(state); // should add error signal 
	str = getcwd(NULL, 0);
	if (str == NULL)
		return (-1);
	else
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
