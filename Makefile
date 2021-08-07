# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 00:12:32 by ybong             #+#    #+#              #
#    Updated: 2021/08/07 11:11:34 by ybong            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRCS = minishell.c\
ms_builtins.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
NAME = minishell.a
OBJS = $(SRCS:.c=.o)
OUT = minishell

LIB = libft.a
LIB_DIR = ./libft


all : $(NAME)

$(NAME) : $(OBJS)
	@make all -C $(LIB_DIR)
	@cp $(LIB_DIR)/$(LIB) $(NAME)
	$(AR) $@ $(OBJS)
	$(CC) $(CFLAGS) $@ -o $(OUT) -lreadline

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean :
	@make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean : clean
	@make fclean -C $(LIB_DIR)
	rm -f $(NAME) $(OUT)


re : fclean all

.PHONY : all clean fclean re
