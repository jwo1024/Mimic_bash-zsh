# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:37:49 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/10/19 15:37:42 by jaeyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

READLINE_LIB	= -lreadline -L/Users/jaeyjeon/.brew/opt/readline/lib
READLINE_INC	= -I/Users/jaeyjeon/.brew/opt/readline/include

LIB_DIR			= ./libft
HEADER			= ./includes
INCLUDES		= -I$(HEADER) -I$(LIB_DIR)

SRC1			= ./srcs/main.c

SRC2			= ./srcs/msh_tree/msh_tree.c \
				  ./srcs/msh_tree/msh_tree_delete.c \
				  ./srcs/signal/signal.c \
				  ./srcs/signal/signal2.c

SRC3			= ./srcs/tokenizer/tokenizer.c \
				  ./srcs/tokenizer/utils.c \
				  ./srcs/tokenizer/get_env.c \
				  ./srcs/tokenizer/get_env2.c \
				  ./srcs/tokenizer/get_env3.c \
				  ./srcs/tokenizer/utils2.c \
				  ./srcs/tokenizer/utils3.c

SRC4			= ./srcs/parser/msh_parser.c \
				  ./srcs/parser/msh_parser2.c \
				  ./srcs/parser/msh_parser_check_type.c \
				  ./srcs/parser/msh_parse_add_simcmd.c \
				  ./srcs/parser/msh_heredoc.c

SRC5			= ./srcs/executor/msh_executor.c \
				  ./srcs/executor/msh_run_cmd.c \
				  ./srcs/executor/msh_redirection.c \
				  ./srcs/executor/msh_error.c \
				  ./srcs/executor/msh_run_builtin.c \
				  ./srcs/executor/msh_executor_fork_wait.c \
				  ./srcs/executor/msh_set_redirection_open.c \
				  ./srcs/executor/msh_executor_utils.c

SRC6			= ./srcs/builtin/do_pwd.c \
				  ./srcs/builtin/do_echo.c \
				  ./srcs/builtin/builtin_utils.c \
				  ./srcs/builtin/do_env.c \
				  ./srcs/builtin/do_cd.c \
				  ./srcs/builtin/do_export.c \
				  ./srcs/builtin/do_export2.c \
				  ./srcs/builtin/builtin_utils2.c \
				  ./srcs/builtin/builtin_utils3.c \
				  ./srcs/builtin/do_unset.c \
				  ./srcs/builtin/do_exit.c

SRCS			= $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6)

OBJS			= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -o $@ -c $<

$(NAME):		$(OBJS)
				make bonus -C $(LIB_DIR)
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
