# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 21:31:47 by seongwch          #+#    #+#              #
#    Updated: 2022/08/18 12:25:46 by junoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
AR = ar
ARFLAGS = rs
RM = rm -f
NAME = shell_libft.a

PART1 = ft_path_join\
	ft_split\
	ft_strdup\
	ft_strichr\
	ft_strlen\
	ft_strncmp\
	ft_strndup\
	get_strchr\
	get_strdup\
	list_struct_ft\
	list_struct\
	list_remove\
	null_strjoin\
	ft_strjoin\
	ft_strchr\
	ft_isalpha\
	ft_itoa\
	ft_atoi\


all : $(NAME)

PART1_SRCS = $(addsuffix .c, $(PART1))
PART1_OBJECTS = $(addsuffix .o, $(PART1))

OBJECTS = $(PART1_OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) $^

$(NAME) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

clean :
	$(RM) $(PART1_OBJECTS)

fclean :
	$(RM) $(NAME) $(PART1_OBJECTS)

re	: fclean all

.PHONY : all re fclean clean
