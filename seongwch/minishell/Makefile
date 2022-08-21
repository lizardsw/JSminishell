# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 15:02:38 by seongwch          #+#    #+#              #
#    Updated: 2022/08/21 16:44:45 by junoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
make = make
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
SHELL_LIBFT_DIR = ./shell_libft/
SHELL_LIBFT = ./shell_libft/shell_libft.a
READLINE_INCLUDE = -I ~/goinfre/.brew/opt/readline/include
READLINE = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include

BUILTIN_DIR = ./source/builtin/
PARSING_DIR = ./source/parsing/
PIPE_DIR = ./source/pipe/
UTILS_DIR = ./source/utils/
INCLUDE_DIR = ./include

BUILTIN_SRC_NAME =	ft_cd.c\
					ft_echo.c\
					ft_env.c\
					ft_exit.c\
					ft_export_print.c\
					ft_export.c\
					ft_pwd.c\
					ft_unset.c\
					
PARSING_SRC_NAME =	expand_utils.c\
					expand_utils2.c\
					expand.c\
					make_ast_utils.c\
					make_ast.c\
					shell_split_utils.c\
					shell_split.c\
					syntax_error.c\

PIPE_SRC_NAME =		execute_cmd.c\
					ft_here_doc.c\
					multi_prc.c\
					pipe_main.c\
					pipe_utils.c\
					setting_fd.c\
					single_prc.c\
					minishell_main.c\

UTILS_SRC_NAME =	free.c\
					ft_error.c\
					ft_no_exit_error.c\
					list_env.c\
					signal.c

BUILTIN_SRC = $(addprefix $(BUILTIN_DIR), $(BUILTIN_SRC_NAME))
PARSING_SRC = $(addprefix $(PARSING_DIR), $(PARSING_SRC_NAME))
PIPE_SRC = $(addprefix $(PIPE_DIR), $(PIPE_SRC_NAME))
UTILS_SRC =  $(addprefix $(UTILS_DIR), $(UTILS_SRC_NAME))

BUILTIN_OBJ = $(BUILTIN_SRC:.c=.o)
PARSING_OBJ = $(PARSING_SRC:.c=.o)
PIPE_OBJ = $(PIPE_SRC:.c=.o)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

%.o : %.c
	$(CC) $(READLINE_INCLUDE) -I $(INCLUDE_DIR) $(CFLAGS) -o $@ -c $^ 

all : $(NAME)

$(SHELL_LIBFT) :
	$(make) -C $(SHELL_LIBFT_DIR) all

$(NAME) : $(SHELL_LIBFT) $(BUILTIN_OBJ) $(PARSING_OBJ) $(PIPE_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $(READLINE) -I $(INCLUDE_DIR) -o $(NAME) $^

clean :
	$(make) -C $(SHELL_LIBFT_DIR) clean
	$(RM) $(BUILTIN_OBJ) $(PARSING_OBJ) $(PIPE_OBJ) $(UTILS_OBJ)

fclean :
	$(make) -C $(SHELL_LIBFT_DIR) fclean
	$(RM) $(BUILTIN_OBJ) $(PARSING_OBJ) $(PIPE_OBJ) $(UTILS_OBJ) $(NAME)

re :
	$(make) fclean
	$(make) all

.PHONY : all re fclean clean