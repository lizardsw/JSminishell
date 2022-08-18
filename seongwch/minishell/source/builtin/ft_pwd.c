/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:03:02 by junoh             #+#    #+#             */
/*   Updated: 2022/08/18 15:20:58 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_list *cmd_list, t_state *state)
{
	char	*str;

	(void)(cmd_list);
	(void)(state);
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
