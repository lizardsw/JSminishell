/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:56:39 by junoh             #+#    #+#             */
/*   Updated: 2022/06/18 20:16:08 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex_bonus.h"

int	open_file(char *file, int flag)
{
	int	open_ret;

	if (flag == 0)
	{
		if (access(file, F_OK) != 0)
			ft_perror(INFILE_OPEN_ERR);
		open_ret = open(file, O_RDONLY);
		if (open_ret < 0)
			ft_perror(INFILE_OPEN_ERR);
		return (open_ret);
	}
	open_ret = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (open_ret < 0)
		ft_perror(OUTFILE_OPEN_ERR);
	return (open_ret);
}
