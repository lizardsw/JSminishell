#include "parsing.h"

void	multi_total_cmd(t_list *cmd, t_state *state)
{
	char *str;

	str = cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(state, cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(cmd, state);
	else
		execute_cmd(cmd, state);
	// else if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	// else if (ft_strncmp(str, "exit",ft_strlen(str)) == 0)
	exit(1);
}

void	single_built_cmd(t_process *storage, t_state *state, t_info *info)
{
	char *str;
	
	// setting_terminal();
	child_signal_handler();
	redir_fd(info, storage->redir);
	str = storage->cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(storage->cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(state, storage->cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(storage->cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(storage->cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(storage->cmd, state);
	else
	{
		printf("execve!\n");
		single_total_cmd(storage, state, info);
	}
	// else if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	// else if (ft_strncmp(str, "exit",ft_strlen(str)) == 0)
}


void	single_total_cmd(t_process *storage, t_state *state, t_info *info)
{
	info->pid[0] = fork();
	if (info->pid[0])
		wait(NULL);
	else
		execute_cmd(storage->cmd, state);
}