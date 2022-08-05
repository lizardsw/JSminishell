/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:56:28 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 14:38:55 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex_bonus.h"

void	*ft_frees(char **strs, char *str)
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
