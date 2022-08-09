/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:38:31 by junoh             #+#    #+#             */
/*   Updated: 2022/08/09 13:03:31 by junoh            ###   ########.fr       */
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
            return ;
        }
        buf = ft_strjoin(buf, "\n");
        write(info->pipe_alpha[1], buf, ft_strlen(buf));
        free(buf);
    }
    close(info->pipe_alpha[1]);
    free(limiter);    
}

int ft_here_doc_redir(t_list *redir, t_info *info)
{
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
    ft_make_pipe(info, 0);
    ft_here_doc_readline(info, limiter);
    return (info->pipe_alpha[0]);
}