/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:54:04 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/18 17:13:05 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_access(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (fd);
	close(fd);
	return (1);
}

static char	*get_path(char **envp, char *cmd)
{
	char	*path;
	char	**real_path;
	int		i;
	int		fd;

	i = 0;
	while (envp[i] != NULL && (ft_strncmp(envp[i], "PATH=", 5)))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_strndup(envp[i] + 5, ft_strlen(envp[i]) - 5);
	real_path = ft_split(path, ':');
	i = 0;
	while (real_path[i] != NULL)
	{
		path = ft_path_join(real_path[i++], cmd);
		fd = ft_access(path);
		if (fd > 0)
		{
			path_frees(real_path, NULL);
			return (path);
		}
	}
	path_frees(real_path, NULL);
	return (cmd);
}

void	execute_cmd(t_list *cmd, t_state *state)
{
	char	*excute_path;
	char	**args;
	char	**envp;
	int		exceve_ret;

	args = make_char_env(cmd);
	envp = make_char_env(state->env_lst);
	if (args[0][0] == '/')
		excute_path = args[0];
	else
		excute_path = get_path(envp, args[0]);
	exceve_ret = execve(excute_path, args, envp);
	if (exceve_ret == -1)
		ft_perror(PATH_ERR);
	ft_perror(EXE_ERR);
}
