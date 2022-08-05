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