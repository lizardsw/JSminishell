# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junoh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 18:25:39 by junoh             #+#    #+#              #
#    Updated: 2022/06/18 18:20:43 by junoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
CC 				= gcc
RM				= rm
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
RMFLAGS			= -f 

SRCS_M 			=	mandatory/pipex.c\
					mandatory/child_proc.c\
					mandatory/exec.c\
					mandatory/free.c\
					mandatory/ft.c\
					mandatory/make_pipe.c\
					mandatory/openfile.c\
					mandatory/parent_proc.c\
					mandatory/put_error.c\
					mandatory/redir.c\
					mandatory/split.c\
					mandatory/util.c\

OBJS_M			= $(SRCS_M:.c=.o)

SRCS_B			=	bonus/pipex_bonus.c\
					bonus/child_proc_bonus.c\
					bonus/free_bonus.c\
					bonus/ft_bonus.c\
					bonus/gnl_bonus.c\
					bonus/here_doc_bonus.c\
					bonus/make_pipe_bonus.c\
					bonus/openfile_bonus.c\
					bonus/parent_proc_bonus.c\
					bonus/put_error_bonus.c\
					bonus/redir_bonus.c\
					bonus/split_bonus.c\
					bonus/exec_bonus.c\
					bonus/util_bonus.c\

OBJS_B			= $(SRCS_B:.c=.o)

HEADER			= 	headers/pipex.h\
					headers/pipex_bonus.h\

all:			$(NAME)

$(NAME):		$(OBJS_M)
				$(CC) ${CFLAGS} -o ${NAME} $^

bonus:			$(OBJS_B)
				$(CC) ${CFLAGS} -o ${NAME} $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $<

clean:
				$(RM) $(RMFLAGS) $(OBJS)

fclean:			clean
				$(RM) $(RMFLAGS) $(OBJS_M) $(OBJS_B)

re:				fclean all

.PHONY:			all clean fclean re
