/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:38:31 by junoh             #+#    #+#             */
/*   Updated: 2022/08/17 17:56:04 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_here_doc_readline(t_info *info, char *limiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (buf == NULL || (ft_strlen(buf) == ft_strlen(limiter) && \
				!ft_strncmp(buf, limiter, ft_strlen(buf))))
		{
			free(buf);
			free(limiter);
			exit(1);
		}
		buf = ft_strjoin(buf, "\n");
		write(info->pipe_alpha[1], buf, ft_strlen(buf));
		free(buf);
	}
	free(limiter);
	exit(1);
}

static int	here_doc_redir(t_node *node, t_info *info)
{
	pid_t	pid;
	t_node	*ptr;
	char	*limiter;

	limiter = NULL;
	limiter = ft_strdup(node->data);
	ft_make_pipe(info);
	pid = fork();
	if (pid == -1)
	{
		ft_no_exit_perror(PID_ERR);
		return (-1);
	}
	else if (pid)
		close(info->pipe_alpha[1]);
	else
		ft_here_doc_readline(info, limiter);
	waitpid(pid, NULL, WUNTRACED);
	return (info->pipe_alpha[0]);
}

int	setting_herdoce(t_process **storage, t_info *info)
{
	t_node	*ptr;
	int		i;
	int		here_num;

	i = 0;
	here_num = 0;
	here_signal_handler();
	while (storage[i] != NULL)
	{
		ptr = storage[i]->redir->start;
		while (ptr != NULL)
		{
			if (ptr->token == RDRDIN)
			{
				ptr = ptr->next;
				ptr->group = here_doc_redir(ptr, info);
				here_num++;
				// printf("flag : %d stats : %d\n", info->prc_flag, g_exit_status);
				if (info->prc_flag == 0 && g_exit_status == 1)
				{
					// printf("hello!\n");
					signal_handler();
					return (-1);
				}
				else if (info->prc_flag == 1 && here_num > 0 && g_exit_status == 1)
				{
					signal_handler();
					return (-1);
				}
			}
			ptr = ptr->next;
		}
		i++;
	}
	signal_handler();
	return (0);
}
