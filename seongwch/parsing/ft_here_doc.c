/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:38:31 by junoh             #+#    #+#             */
/*   Updated: 2022/08/09 21:16:05 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void ft_here_doc_readline(t_info *info, char *limiter)
{
    char    *buf;

    while (1)
    {
        // write(STDOUT_FILENO, "> ", 2);
        buf = readline("> ");
        if (buf == NULL || (ft_strlen(buf) == ft_strlen(limiter) &&\
        !ft_strncmp(buf, limiter, ft_strlen(buf))))
        {
            free(buf);
            free(limiter);
            // return ;
            exit(1);
        }
        buf = ft_strjoin(buf, "\n");
        write(info->pipe_beta[1], buf, ft_strlen(buf));
        free(buf);
    }
    free(limiter);
    exit(1);
    // return ;
}

int ft_here_doc_redir(t_list *redir, t_info *info)
{
    pid_t   pid;
    t_node  *ptr;
    char    *limiter;
    
    limiter = NULL;
    ptr = redir->start;
    while (ptr != NULL)
    {
        if (!ft_strncmp(ptr->data, "<<", 2) && ft_strlen(ptr->data) == 2)
        {
            limiter = ft_strdup(ptr->next->data);
            break ;
        }
        ptr = ptr->next;
    }
    ft_make_pipe(info, 1);
    pid = fork();
    if (pid)
    {
        close(info->pipe_beta[1]);
    }
    else
        ft_here_doc_readline(info, limiter);
    waitpid(pid, NULL, WUNTRACED);
    return (info->pipe_beta[0]);
}