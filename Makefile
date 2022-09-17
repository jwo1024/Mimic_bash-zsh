# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:37:49 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/09/17 18:29:02 by jaeyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

READLINE_LIB	= -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/.brew/opt/readline/include

LIB_DIR		= ./inc/42Libft

SRCS			= test.c

OBJS			= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -o $@ -c $<

$(NAME):		$(OBJS)
				make -C $(LIB_DIR)
				$(CC) $(CFLAGS) $(READLINE_LIB) $(READLINE_INC) -L $(LIB_DIR) -lft -o $(NAME) $(OBJS)

all:			$(NAME)

clean:
				make -C $(LIB_DIR) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(LIB_DIR) clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			clean fclean all re
