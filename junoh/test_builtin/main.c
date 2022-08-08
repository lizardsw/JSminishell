/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:56:36 by junoh             #+#    #+#             */
/*   Updated: 2022/08/08 16:14:19 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void    put_var_to_process(t_process *process)
{
    t_list *list;

    list = new_list();
    push_node_front(list, new_node("export"));
    push_node_back(list, new_node("a=12"));
    push_node_back(list, new_node("a=123"));
    push_node_back(list, new_node("c"));
    process->cmd = list;
}

void    put_var_to_process_two(t_process *process)
{
    t_list *list;

    list = new_list();
    push_node_front(list, new_node("unset"));
    push_node_back(list, new_node("a"));
    push_node_back(list, new_node("b"));
    push_node_back(list, new_node("c"));
    process->cmd = list;
}

void    put_var_to_process_thrid(t_process *process)
{
    t_list *list;

    list = new_list();
    push_node_front(list, new_node("export"));
    process->cmd = list;
}

void    put_var_to_process_pwd(t_process *process)
{
    t_list *list;

    list = new_list();
    push_node_front(list, new_node("pwd"));
    process->cmd = list;
}

void    put_var_to_process_cd(t_process *process, char *cmd)
{
    t_list *list;

    list = new_list();
    push_node_front(list, new_node("cd"));
    if (cmd != NULL)
        push_node_back(list, new_node(cmd));
    process->cmd = list;
}

int main(int argc, char **argv, char **env)
{
    t_state state;
    t_process storage;
    pid_t pid;
    t_node *cmd_node;
    t_node *env_node;
    
    ft_memset(&state, 0, sizeof(state));
    ft_memset(&storage, 0, sizeof(storage));
    state.env_lst = make_list_env(env);
    put_var_to_process(&storage);
    cmd_node = storage.cmd->start;
    env_node = new_node("env");
    ft_env(&state, env_node);
    ft_export(storage.cmd, &state);
    ft_env(&state, env_node);
    printf("\n");
    put_var_to_process_two(&storage);
    ft_export(storage.cmd, &state);
    ft_unset(storage.cmd, &state);
    ft_env(&state, env_node); 
    put_var_to_process_thrid(&storage);
    ft_export(storage.cmd, &state); 
    // put_var_to_process_pwd(&storage);
    // ft_pwd(storage.cmd, &state);
    // put_var_to_process_cd(&storage, "/Users/junoh/Desktop/minilibx/test");
    // ft_cd(storage.cmd, &state);
    // ft_pwd(storage.cmd, &state);
    // put_var_to_process_cd(&storage, NULL);
    // ft_cd(storage.cmd, &state);
    // ft_pwd(storage.cmd, &state);
    return (0);
}