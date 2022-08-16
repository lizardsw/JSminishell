#include "parsing.h"

void	multi_total_cmd(t_list *cmd, t_state *state)
{
	char *str;

	if (cmd->start == NULL)
		exit(1) ;
	str = cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		ft_env(state, cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		ft_unset(cmd, state);
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(str, "exit",ft_strlen("exit")) == 0)
		ft_exit(cmd, state);
	else
		execute_cmd(cmd, state);
	exit(1);
}

static void	single_total_cmd(t_process *storage, t_state *state, t_info *info)
{
	info->pid[0] = fork();
	if (info->pid[0] == -1)
	{
		ft_no_exit_error(PID_ERR);
		return ;
	}
	if (info->pid[0])
		waitpid(info->pid[0], NULL, WUNTRACED);
	else
		execute_cmd(storage->cmd, state);
}

void	single_built_cmd(t_process *storage, t_state *state, t_info *info)
{
	char *str;
	
	if(redir_fd(info, storage->redir) == -1)
		return ;
	if (storage->cmd->start == NULL)
		return ;
	str = storage->cmd->start->data;
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(storage->cmd, state);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		ft_env(state, storage->cmd->start);
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(storage->cmd, state);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(storage->cmd, state);
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		ft_unset(storage->cmd, state);
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(storage->cmd);
	else if (ft_strncmp(str, "exit",ft_strlen("exit")) == 0)
		ft_exit(storage->cmd, state);
	else
		single_total_cmd(storage, state, info);
}
