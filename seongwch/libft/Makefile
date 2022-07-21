# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongwch <seongwch@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 21:31:47 by seongwch          #+#    #+#              #
#    Updated: 2021/12/11 18:11:00 by seongwch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
AR = ar
ARFLAGS = rs
RM = rm -f
NAME = libft.a


PART1 = ft_atoi\
	ft_isascii\
	ft_memcmp\
	ft_strchr\
	ft_strncmp\
	ft_toupper\
	ft_bzero\
	ft_isdigit\
	ft_memcpy\
	ft_strlcat\
	ft_strnstr\
	ft_isalnum\
	ft_isprint\
	ft_memmove\
	ft_strlcpy\
	ft_strrchr\
	ft_isalpha\
	ft_memchr\
	ft_memset\
	ft_strlen\
	ft_tolower\
	ft_strdup\
	ft_calloc

PART2 = ft_itoa\
	ft_putchar_fd\
	ft_putendl_fd\
	ft_putnbr_fd\
	ft_putstr_fd\
	ft_split\
	ft_striteri\
	ft_strjoin\
	ft_strmapi\
	ft_strtrim\
	ft_substr

BONUS = ft_lstadd_back\
	ft_lstclear\
	ft_lstiter\
	ft_lstsize\
	ft_lstadd_front\
	ft_lstdelone\
	ft_lstlast\
	ft_lstnew\
	ft_lstmap


all : $(NAME)

PART1_SRCS = $(addsuffix .c, $(PART1))
PART1_OBJECTS = $(addsuffix .o, $(PART1))

PART2_SRCS = $(addsuffix .c, $(PART2))
PART2_OBJECTS = $(addsuffix .o, $(PART2))

BONUS_SRCS = $(addsuffix .c, $(BONUS))
BONUS_OBJECTS = $(addsuffix .o, $(BONUS))

ifdef WITH_BONUS
	OBJECTS = $(PART1_OBJECTS) $(PART2_OBJECTS) $(BONUS_OBJECTS)
else
	OBJECTS = $(PART1_OBJECTS) $(PART2_OBJECTS)
endif

%.o : %.c
	$(CC) $(CFLAGS) $^

$(NAME) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

clean :
	$(RM) $(PART1_OBJECTS) $(PART2_OBJECTS) $(BONUS_OBJECTS)

fclean :
	$(RM) $(NAME) $(PART1_OBJECTS) $(PART2_OBJECTS) $(BONUS_OBJECTS)

re	: fclean all

bonus	: 
	make WITH_BONUS=1 all

.PHONY : all bonus re fclean clean
