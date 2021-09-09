# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybong <ybong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 00:12:32 by ybong             #+#    #+#              #
#    Updated: 2021/09/09 16:50:25 by ybong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = minishell.c\
ms_modify_buf.c\
ms_fill_data.c\
ms_get_cmd_path.c\
ms_utils.c\
builtins/bi_env.c\
builtins/bi_export.c\
builtins/bi_cd.c\
redirect/re_insert_space.c\
redirect/re_get_re.c\
redirect/redir.c\
redirect/re_redirect.c

CC = gcc
CFLAGS = -fsanitize=address -Wall -Wextra -Werror 
AR = ar rcs
NAME = minishell.a
OBJS = *.o  #$(SRCS:.c=.o)
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
