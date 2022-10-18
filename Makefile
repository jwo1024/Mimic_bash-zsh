# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:37:49 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/10/18 15:11:08 by jiwolee          ###   ########seoul.kr   #
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
INCLUDES		= -I$(HEADER) -I$(LIB_DIR)

SRC1			= main.c

SRC2			= ./msh_tree/msh_tree.c \
				  ./msh_tree/msh_tree_delete.c \
				  ./msh_tree/msh_tree_print.c \
				  ./parser/msh_parser.c \
				  ./parser/msh_parser2.c \
				  ./executor/msh_executor.c \
				  ./executor/msh_run_cmd.c \
				  ./executor/msh_redirection.c \
				  ./executor/msh_error.c \
				  ./executor/msh_run_builtin.c \
				  ./executor/msh_executor_fork_wait.c \
				  ./executor/msh_heredoc.c \
				  ./parser/msh_parser_check_type.c

SRC3			= ./tokenizer/tokenizer.c \
				  ./tokenizer/utils.c \
				  ./tokenizer/get_env.c \
				  ./tokenizer/get_env2.c \
				  ./tokenizer/get_env3.c \
				  ./tokenizer/utils2.c \
				  ./tokenizer/utils3.c \
				  ./builtin/do_pwd.c \
				  ./builtin/do_echo.c \
				  ./builtin/builtin_utils.c \
				  ./builtin/do_env.c \
				  ./builtin/do_cd.c \
				  ./builtin/do_export.c \
				  ./builtin/do_export2.c \
				  ./builtin/builtin_utils2.c \
				  ./builtin/builtin_utils3.c \
				  ./builtin/do_unset.c \
				  ./builtin/do_exit.c \
				  ./signal/signal.c \
				  ./signal/signal2.c

SRCS			= $(SRC1) $(SRC2) $(SRC3)

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
