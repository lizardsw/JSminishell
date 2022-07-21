/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:18:12 by junoh             #+#    #+#             */
/*   Updated: 2022/06/28 15:40:56 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

# define BUFFER_SIZE 42

typedef struct s_info
{
	int		fdin;
	int		fdout;
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_alpha[2];
	int		pipe_beta[2];
	pid_t	*pid;
	int		flag;
	int		status;
}				t_info;

enum e_error
{
	ARGS_NUM_ERR,
	PID_ERR,
	INFILE_OPEN_ERR,
	OUTFILE_OPEN_ERR,
	PATH_ERR,
	EXE_ERR,
	PIPE_ERR,
	DUP_ERR
};

int		open_file(char *file, int flag);

void	execute_cmd(char *cmd, char **envp);

int		ft_redir(t_info *info);

void	ft_child_proc(t_info *info, int index);

void	ft_make_pipe(t_info *info, int index);

void	ft_parent_proc(t_info *info, int index);

int		ft_strlen(char *str);

int		ft_strichr(const char *s, int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strndup(const char *s, int cpy_len);

char	*ft_path_join(char *left_string_buf, char *read_buf);

char	**ft_split(char const *s, char c);

char	*ft_frees(char **strs, char *str);

pid_t	ft_fork(void);

int		ft_dup2(int fd1, int fd2);

int		ft_close(int fd);

void	ft_put_cmd_err(char *cmd);

char	*str_join(char *s1, char *s2);

void	ft_error(int err);

int		ft_perror(int err);

int		ft_check_status(t_info *info);

#endif
