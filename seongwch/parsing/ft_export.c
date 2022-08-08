/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:10:39 by junoh             #+#    #+#             */
/*   Updated: 2022/08/09 05:59:01 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int export_check_str(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] >= 48 && str[i] <= 57) || str[i] == '=' || str[i] == '_' ||  
            ft_isalpha(str[i]))
            i++;
        else
            return (0);
    }
    return (1);
}

void    replace_node(t_node *new_node, t_list *env_lst)
{
    t_node *ptr;
    char    **origin;
    char    **args;
    char    *tmp;
    
    args = split_key_value(new_node->data);
    ptr = env_lst->start;
    while (ptr != NULL)
    {
        origin = split_key_value(ptr->data);
        if (compare_str(origin[0], args[0]))
        {
            tmp = ptr->data;
            ptr->data = ft_strdup(new_node->data);
            free(tmp);
            free_str(args);
            free_str(origin);
            return ;
        }
        free_str(origin);
        ptr = ptr->next;
    }
    free_str(args);
}

void     check_key(t_node *node, t_list *env_lst)
{
    char    **origin;
    char    **args;
    t_node  *ptr;

    ptr = env_lst->start;
    args = split_key_value(node->data);
    while (ptr != NULL)
    {
        origin = split_key_value(ptr->data);
        if (compare_str(args[0], origin[0]))
        {
            classify_export(args, origin, node, 1, env_lst);
            free_str(args);
            free_str(origin);
            return ;            
        }
        free_str(origin);
        ptr = ptr->next;
    }
    classify_export(args, NULL, node, 0, env_lst);
    free_str(args);
    return ;
}

void    classify_export(char **args, char **origin, t_node *arg_node, \
int flag, t_list *env) // flag = 0 는 arg_node 의 키값이 없는 경우
{
    if (flag == 0 || !compare_str(origin[0], args[0]))
        push_node_back(env, new_node(arg_node->data));
    else if (origin[0] && origin[1] == NULL)
    {
        if (compare_str(origin[0], args[0]) && 
        !ft_strncmp(arg_node->data, origin[0], ft_strlen(origin[0]) &&
        ft_strlen(arg_node->data) - 1 == ft_strlen(origin[0])))
            replace_node(arg_node, env);
    }
    else if (origin[0] && origin[1])
    {
        if (compare_str(origin[0], args[0]) && 
        !compare_str(origin[1], args[1]) &&
		ft_strlen(origin[0]) != 0)
            replace_node(arg_node, env);
    }
}

void    ft_export(t_list *cmd_list, t_state *state)
{
    t_node *cmd_ptr;
    
    cmd_ptr = cmd_list->start;
    if (cmd_ptr->next == NULL)
    {
        export_print(state);
        return ;
    }
    cmd_ptr = cmd_ptr->next;
    while (cmd_ptr != NULL)
    {   
        if (ft_strlen(cmd_ptr->data) == 1 && cmd_ptr->data[0] == '_')
            ;
        else if (!ft_isalpha(cmd_ptr->data[0]))
           printf("bash: export: `%c\': not a valid identifier\n", cmd_ptr->data[0]);
        else if (!export_check_str(cmd_ptr->data))
           printf("bash: export: `%s\': not a valid identifier\n", cmd_ptr->data); 
        else
            check_key(cmd_ptr, state->env_lst);
        cmd_ptr = cmd_ptr->next;
    }
}