/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:02:13 by junoh             #+#    #+#             */
/*   Updated: 2022/07/26 17:55:08 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void    ft_cd(t_node *cmd_node, t_state *state)
{

    if (cmd_node->next != NULL || cmd_node->next->data == "~")
        chdir("home") // state->env_list에서 "HOME"에 해당되는 path를 넣어야 함.
    
    
}