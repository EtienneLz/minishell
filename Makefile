NAME = minishell

SRCS = srcs/minishell.c \
		srcs/utils/utils1.c \
		srcs/parsing/split_command.c \
		srcs/init/struct_init.c \
		srcs/builtins/exit.c \
		srcs/parsing/tokenizer.c \
		srcs/execution/execution.c \

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCBONUS:.c=.o}

PATH_LIBFT = 42_libft

INCLUDES = -I/includes/minishell.h

CFLAGS = -g #-Werror -Wall -Wextra #-fsanitize=address

GCC = gcc 

LIB = 42_libft/libft.a -I./usr/include

RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		make -C $(PATH_LIBFT)
		${GCC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIB} -o ${NAME} -lreadline

clean:
		make -C $(PATH_LIBFT) clean
		${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
		make -C $(PATH_LIBFT) clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re
