/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:38:41 by junoh             #+#    #+#             */
/*   Updated: 2022/07/28 15:42:02 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

pid_t   ft_fork(void)
{
    pid_t   ret_pid;

    ret_pid = fork();
    if (ret_pid == -1)
        perror("Invaild pid");
    return (ret_pid);
}