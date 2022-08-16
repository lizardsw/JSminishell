/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:38:31 by junoh             #+#    #+#             */
/*   Updated: 2022/08/16 20:00:07 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void ft_here_doc_readline(t_info *info, char *limiter)
{
    char    *buf;

    while (1)
    {
        buf = readline("> ");
        if (buf == NULL || (ft_strlen(buf) == ft_strlen(limiter) &&\
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

static int here_doc_redir(t_node *node, t_info *info)
{
    pid_t   pid;
    t_node  *ptr;
    char    *limiter;
    
    limiter = NULL;
    limiter = ft_strdup(node->data);
    ft_make_pipe(info, 1);
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

void    setting_herdoce(t_process **storage, t_info *info)
{
    t_node  *ptr;
    int      i;

    i = 0;
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
            }
            ptr = ptr->next;
        }
        i++;
    }
    signal_handler();
}