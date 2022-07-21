/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:56:28 by junoh             #+#    #+#             */
/*   Updated: 2022/06/28 17:00:18 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex_bonus.h"

char	*ft_frees(char **strs, char *str)
{
	int	i;

	i = 0;
	if (strs != NULL)
	{
		while (strs[i] != NULL)
			free(strs[i++]);
		free(strs[i]);
		free(strs);
		return (NULL);
	}
	else
		free(str);
	return (NULL);
}
