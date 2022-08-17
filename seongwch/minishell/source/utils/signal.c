/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwch <seongwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:31:56 by seongwch          #+#    #+#             */
/*   Updated: 2022/08/17 16:10:18 by seongwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setting_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static	void	handler(int signum)
{
	pid_t	pid;

	if (signum != SIGINT)
		return ;
	pid = waitpid(-1, NULL, WNOHANG);
	if (pid != 0)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		write(STDOUT_FILENO, "^C\n", 3);
}

void	signal_handler(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

static	void	here_handler(int signum)
{
	pid_t	pid;

	if (signum != SIGINT)
		return ;
	pid = waitpid(-1, NULL, WNOHANG);
	if (pid != 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(1);
	}
}

void	here_signal_handler(void)
{
	signal(SIGINT, here_handler);
	signal(SIGQUIT, SIG_IGN);
}
