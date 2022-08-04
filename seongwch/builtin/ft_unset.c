/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:26:06 by junoh             #+#    #+#             */
/*   Updated: 2022/08/04 14:59:40 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void    exec_unset(t_node *cmd_node, t_state *state)
{
    t_node *ptr;

    ptr = cmd_node;
    if ()
}

void    ft_unset(t_list *cmd_list, t_state *state)
{
    pid_t   pid;
    
    pid = 0;
    if (cmd_list->pipe_num == 0)
        exec_unset(cmd_list->start, state);
    else
    {
        pid = ft_fork();
        if (pid)
            wait(&state->status);
        else
        {
            exec_unset(cmd_list->start, state);
            exit(0);
        }
    }
    return ;
}

