# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/13 18:49:11 by elouchez          #+#    #+#              #
#    Updated: 2022/01/05 17:20:22 by elouchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c  ft_strcmp.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_split.c \

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCBONUS:.c=.o}

GCCFLAGS = -Wall -Werror -Wextra

RM  = rm -f

.c.o:
	gcc ${GCCFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}:	${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

bonus:		${OBJSBONUS} ${OBJS}
	ar rc ${NAME} ${OBJS} ${OBJSBONUS}
	ranlib ${NAME}

clean:
	${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
	${RM} ${NAME}

re : fclean all

.PHONY: clean fclean re
