/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:35:37 by junoh             #+#    #+#             */
/*   Updated: 2022/08/09 12:53:57 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static  void ft_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
    return ;
}

static  void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
        ft_putchar(str[i++]);
    return ;
}

static  void    print_echo(t_list *cmd_list, int flag)
{
    t_node *ptr;

    ptr = cmd_list->start->next;
    if (flag == 1)
    {
        if (ptr->next == NULL) // echo -n 인 경우
            return ;
        ptr = ptr->next; // echo -n a b c ...
    }
    while (ptr != NULL)
    {
        ft_putstr(ptr->data);
        ft_putchar(' ');    
        ptr = ptr->next;
    }
    return ;
}

void    ft_echo(t_list *cmd_list)
{
    t_node *ptr;
    int     flag;
    
    
    ptr = cmd_list->start;
    flag = 0;
    if (ptr->next == NULL)
    {
        write(STDOUT_FILENO, "\n", 1);
        return ;
    }
    if (!ft_strncmp(cmd_list->start->next->data, "-n", ft_strlen("-n")))
        flag = 1;
    print_echo(cmd_list, flag);
    if (flag == 0)
        write(STDOUT_FILENO, "\n", 1);
    return ;
}