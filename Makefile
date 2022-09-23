# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:37:49 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/09/23 19:22:21 by jiwolee          ###   ########seoul.kr   #
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

SRC1			= main.c

SRC2			= ./msh_tree/msh_tree.c \
				  ./msh_tree/msh_tree_delete.c \
				  ./msh_tree/msh_tree_print.c \
				  ./parser/msh_parser.c \
				  ./parser/msh_parser2.c

SRC3			= ./tokenizer/tokenizer.c \
				  ./tokenizer/utils.c \
				  ./tokenizer/signal.c \
				  ./tokenizer/get_env.c \
				  ./tokenizer/utils2.c

SRCS			= $(SRC1) $(SRC2) $(SRC3)

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
