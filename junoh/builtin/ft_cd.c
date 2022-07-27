/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:02:13 by junoh             #+#    #+#             */
/*   Updated: 2022/07/27 15:10:29 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void    change_env_path(t_state *state, char *key)
{
    char *buf;

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
        new_node(ft_strjoin("OLDPWD=", state->pwd)));
    state->old_pwd = state->pwd;
    buf = state->pwd;
    state->pwd = getcwd(NULL, 0);
    free(buf);
}
void    ft_cd(t_node *cmd_node, t_state *state)
{
    if (cmd_node->next != NULL || cmd_node->next->data == "~")
        chdir(get_value(state->env_lst, "HOME"));
    else if (chdir(cmd_node->next->data))
    {
    chdir(state->pwd); // cd 실패시 현재 디렉토리로 cd 수정
    printf("minishell: cd: {%s}: No such file or directory\n",\
    cmd_node->next->data);
    }
}