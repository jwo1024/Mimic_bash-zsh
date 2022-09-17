# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 19:29:07 by jaeyjeon          #+#    #+#              #
#    Updated: 2022/01/20 02:08:30 by jaeyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

SRCS		= ft_memset.c ft_memmove.c ft_memcpy.c ft_isprint.c ft_isdigit.c \
				ft_isascii.c ft_isalpha.c ft_isalnum.c ft_bzero.c ft_strlcat.c \
				ft_strlcpy.c ft_tolower.c ft_toupper.c ft_strchr.c \
				ft_strrchr.c ft_strlen.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_strncmp.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c \
				ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c

SRCS_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS) $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS)
endif

all:		$(NAME)

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME):	$(OBJ_FILES)
				ar crs $(NAME) $(OBJ_FILES)

bonus :
	make WITH_BONUS=1 all

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
				$(RM) $(NAME)
				$(RM) libft.h.gch

re:			fclean $(NAME)

.PHONY:		bonus all clean fclean re
