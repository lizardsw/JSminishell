/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:35:37 by junoh             #+#    #+#             */
/*   Updated: 2022/08/17 17:03:03 by seongwch         ###   ########.fr       */
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
    int     arg;

    arg = 0;
    ptr = cmd_list->start->next;
    if (flag == 1)
    {
        if (ptr->next == NULL) // echo -n 인 경우
            return ;
        ptr = ptr->next; // echo -n a b c ...
    }
    while (ptr != NULL)
    {
        if (ft_strncmp(ptr->data, "-n", ft_strlen("-n")) || arg)
        {
            arg = 1;
            ft_putstr(ptr->data);
        }
        if (ft_strncmp(ptr->data, "-n", ft_strlen("-n")) && \
        ptr->next != NULL)
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