# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:37:49 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/09/23 16:29:26 by jaeyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

LIB_DIR			= ./libft
HEADER			= ./includes
INCLUDES		= -I$(HEADER)

SRC1			= ./msh_tree/msh_tree.c

SRCS			= test.c ./tokenizer/tokenizer.c ./tokenizer/utils.c \
				./tokenizer/signal.c ./tokenizer/get_env.c ./tokenizer/utils2.c \
				$(SRC1)

OBJS			= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -o $@ -c $<

$(NAME):		$(OBJS)
				make -C $(LIB_DIR)
				$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_LIB) $(READLINE_INC) -L $(LIB_DIR) -lft -o $(NAME) $(OBJS)

all:			$(NAME)

clean:
				make -C $(LIB_DIR) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(LIB_DIR) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			clean fclean all re
