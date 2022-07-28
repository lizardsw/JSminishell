/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:10:39 by junoh             #+#    #+#             */
/*   Updated: 2022/07/28 15:51:20 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

t_node     *is_key_exist_without_value(t_state *state, char *key, int flag)
{
    t_node *lst = state->env_lst->start;
    char    *cmp_buf;
    char    **split;
    
    cmp_buf = get_strdup(key, (int)ft_strlen(key) - flag);
    while (lst->next != NULL)
    {
        split = split_key_value(lst->data);
        if ((!ft_strncmp(cmp_buf, split[0], (int)ft_strlen(key) - flag) && \
        ((int)ft_strlen(split[0]) == (int)ft_strlen(key) - flag)))
        {
            free_str(split);
            return (lst);
        }
        lst = lst->next;
    }        
    free_str(split);
    return (NULL);
}

void    change_and_add_env_lst(t_state *state, char **split, t_node *cmd_node)
{
    t_node *node;
       
    node = is_key_exist_without_value(state, split[0], 1);
    if (node)
    {
        node->data = ft_strjoin(node->data, "=");
        node->data = ft_strjoin(node->data, split[1]);
    }
    else
    {
        node = is_key_exist_without_value(state, split[0], 0);
        if (node)
            node->data = ft_strjoin(node->data, split[1]);
        else
            push_node_back(state->env_lst, new_node(cmd_node->data));
    }
    free_str(split);
    return ;
}

void    change_env_lst(t_node *node, t_state *state)
{
    char    **morpheme; 
    t_node  *n_node;
        
    morpheme = split_key_value(node->data);
    n_node = NULL;
    morpheme[0] = ft_strjoin(morpheme[0], "="); // ft_strjoin 수정함
    if (morpheme[1] == '\0') // export a=
    { 
        n_node = is_key_exist_without_value(state, morpheme[0], 1);
        if (n_node)
            n_node->data = ft_strjoin(n_node->data, "=");
        else
            push_node_back(state->env_lst, new_node(morpheme[0]));
        free_str(morpheme);
    }
    else
        change_and_add_env_lst(state, morpheme, node);
}

void    exec_export(t_node *cmd_node, t_state *state)
{
    t_node *ptr;
    
    ptr = cmd_node;
    if (ptr->next == NULL)
        export_print(state);
    else
    {
        while (ptr->next != NULL)
        {
            if (!ft_strchr(cmd_node->next, '='))
                change_env_lst(ptr, state);
            else
                push_node_back(state->env_lst, new_node(ptr->data));
            ptr = ptr->next;
        }
    }
    return ;
}

void    ft_export(t_list *cmd_list, t_state *state)
{
    pid_t   pid;

    pid = 0;
    if (cmd_list->pipe_num == 0)
        exec_export(cmd_list->start, state);
    else
    {
        pid = ft_fork();
        if (pid)
            wait(&state->status);
        else
        {
            exec_export(cmd_list->start, state);
            exit(0);
        }
    }
    return ;
}