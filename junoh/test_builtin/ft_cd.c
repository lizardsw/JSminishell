/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:02:13 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 19:52:08 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void    change_env_path(t_state *state, char *key, int flag)
{
    t_node *node;
    char    *buf;

    buf = NULL;
    node = state->env_lst->start;
    while (node->next != NULL)
    {
        if (!ft_strncmp(key, node->data, (int)ft_strlen(key))) // ft_strncmp pass
        {
            buf = node->data;
            if (flag == 0)
                node->data = ft_strdup(state->old_pwd); //ft_strdup pass
            else
                node->data = ft_strdup(state->pwd);
            free(buf);
        }
        node = node->next;
    }
    return ;
}

void    change_dir(char *path, t_state *state)
{
    int     ret;
    char    *buf;

    ret = chdir(path);
    if (ret == 0)
    {
        if (state->old_pwd == NULL)
            push_node_back(state->env_lst, \
            new_node(ft_strjoin("OLDPWD=", state->pwd))); // ft_strjoin make
        state->old_pwd = state->pwd;
        buf = state->pwd;
        state->pwd = getcwd(NULL, 0);
        change_env_path(state, "OLDPWD=", 0);
        change_env_path(state, "PWD=", 1);
        free(buf);
    //    printf("cd : %s\n", state->pwd);
    }
    else
        printf("minishell: cd: {%s}: No such file or directory\n", path);
    return ;
}

void    ft_cd(t_list *cmd_list, t_state *state)
{
    t_node *node;

    node = cmd_list->start;
    if (state->pwd == NULL)
        state->pwd = getcwd(NULL, 0);
    if (node->next == NULL || node->next->data[0] == '~')
        change_dir(get_value(state->env_lst, "HOME"), state);
    else if (node->next->data[0] == '\0')
        return ;
    else
        change_dir(node->next->data, state);
}