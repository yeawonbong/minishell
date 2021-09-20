# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybong <ybong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 00:12:32 by ybong             #+#    #+#              #
#    Updated: 2021/09/20 16:39:04 by ybong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./minishell.c\
./ms_modify_buf.c\
./ms_modify_envar.c\
./ms_fill_data.c\
./ms_get_cmd_path.c\
./ms_utils.c\
./ms_signal.c\
./builtins/bi_env.c\
./builtins/bi_in_child.c\
./builtins/bi_in_parent.c\
./builtins/builtins.c\
./redirect/re_insert_space.c\
./redirect/re_get_re.c\
./redirect/redir.c\
./redirect/re_redirect.c

CC = gcc #-fsanitize=address
CFLAGS =  -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include #-lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
#  -fsanitize=addressCFLAGS = -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
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
	@$(AR) $@ $(OBJS)
	$(CC) $(CFLAGS) $@ -o $(OUT)

clean :
	@make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean : clean
	@make fclean -C $(LIB_DIR)
	rm -f $(NAME) $(OUT)


re : fclean all

.PHONY : all clean fclean re
