/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:03:02 by junoh             #+#    #+#             */
/*   Updated: 2022/07/26 15:47:04 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

// 이전 함수에서 dup2(fd, STDOUT) 이 되어있음

int ft_pwd(t_node *cmd_node, t_state *state)
{
    char    *str;

    (void)(cmd_node);
    str = getcwd(NULL, 0);
    if (str == NULL)
        return (-1);
    else
    {
        printf("%s\n", str);
        free(str);
    }
    return (0);
}
