/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:35:11 by junoh             #+#    #+#             */
/*   Updated: 2022/06/18 21:10:17 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static	void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

void	ft_setting(int ac, char **av, char **env, t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->argc = ac;
	info->argv = av;
	info->envp = env;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * (ac - 3));
	if (info->pid == NULL)
		exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		ret;

	ret = 0;
	if (ac != 5)
		ft_error(ARGS_NUM_ERR);
	else
	{
		ft_setting(ac, av, env, &info);
		info.fdin = open_file(av[1], STDIN_FILENO);
		ret = ft_redir(&info);
		free(info.pid);
	}
	return (ret);
}
