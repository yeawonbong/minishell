# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sma <sma@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/03 17:23:38 by sma               #+#    #+#              #
#    Updated: 2021/07/04 16:35:39 by sma              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libpipex.a
PIPEX		= pipex
LIBFT		= libft
LIBFT_LIB	= libft.a

SRCS		=./pipex.c\
			./split_parsing.c\
			./redirection.c\
			
OBJS		= $(SRCS:.c=.o)
RM			= rm -f
LIBC		= ar rc
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I .

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(NAME) -I . -o $(PIPEX)

all : $(NAME)

fclean : clean
	$(RM) $(NAME) $(PIPEX)
	make fclean -C $(LIBFT)

clean :
	$(RM) $(OBJS)
	make clean -C $(LIBFT)

re : fclean all