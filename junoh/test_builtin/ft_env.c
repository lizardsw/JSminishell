/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:42:25 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 19:54:56 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

int ft_env(t_state *state, t_node *cmd_node)
{
    t_node *node;

    if (cmd_node->next != NULL)
    {
        printf("env: %s: No such file or directory\n", cmd_node->next->data);
        return (-1);
    }
    else
    {
        node = state->env_lst->start;
        while (node->next != NULL)
        {
            if (ft_strchr(node->data, '=')) // ft_strchr make
                printf("%s\n", node->data);
            node = node->next;
        }
        return (0); // env 성공 시 리턴 0  이지만 실패할 경우를 모르겠음.
    }
}